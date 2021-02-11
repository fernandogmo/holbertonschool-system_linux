use std::io::{prelude::*, Read, SeekFrom};
use std::vec::Vec;
use std::{convert::TryInto, env::args};
use std::{
    fs::{read_to_string, OpenOptions},
    process::exit,
};

fn main() -> std::io::Result<()> {
    let prog_name = args().nth(0).unwrap();
    if let [pid, oldstr, newstr] = &args().skip(1).collect::<Vec<_>>()[..] {
        Ok(read_write_heap(pid, oldstr, newstr)?)
    } else {
        eprintln!("Usage: {} <pid> <old-string> <new-string>", prog_name);
        exit(1)
    }
}

// TODO: add some tests
// TODO: split into functions
fn read_write_heap(pid: &str, oldstr: &str, newstr: &str) -> std::io::Result<()> {
    if newstr.len() > oldstr.len() {
        eprintln!("<new-string> cannot be longer than <old-string>");
        exit(1);
    };
    // TODO: better error message here
    let maps_file = read_to_string(format!("/proc/{}/maps", pid))?;
    let line = maps_file
        .lines()
        .find(|x| x.contains("[heap]"))
        .expect("Couldn't find heap in /proc/<pid>/maps");
    let [start, end]: [usize; 2] = line
        .splitn(3, &[' ', '-'][..])
        .collect::<Vec<_>>()
        .iter()
        .filter_map(|x| usize::from_str_radix(x, 16).ok())
        .collect::<Vec<_>>()
        .try_into()
        .expect("Couldn't parse heap addresses");
    let mut mem_file = OpenOptions::new()
        .read(true)
        .write(true)
        .open(format!("/proc/{}/mem", pid))?;
    let mut heap = Vec::new();
    mem_file.seek(SeekFrom::Start(start as u64))?;
    Read::by_ref(&mut mem_file)
        .take((end - start) as u64)
        .read_to_end(&mut heap)?;
    if let None = heap.windows(oldstr.len()).enumerate()
        .fold(None, |acc, (i, w)| {
            acc.or((w == oldstr.as_bytes()).then(|| {
                mem_file.seek(SeekFrom::Start((start + i) as u64)).unwrap();
                mem_file.write(newstr.as_bytes()).ok()
            }))
        })
    {
        eprintln!("Couldn't find `{}` on the heap", oldstr);
        exit(1);
    };
    Ok(())
}
