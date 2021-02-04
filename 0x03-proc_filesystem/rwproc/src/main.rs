use std::env::args;
use std::fs::{read_to_string, OpenOptions};
use std::io;
use std::io::{prelude::*, Read, SeekFrom};
use std::vec::Vec;

fn main() -> std::io::Result<()> {
    if let [_, pid, oldstr, newstr] = &args().collect::<Vec<_>>()[..] {
        read_write_heap(pid, oldstr, newstr)?;
    } else {
        eprintln!("Usage: ./read_write_heap <pid> <old-string> <new-string>");
    }
    Ok(())
}

fn read_write_heap(pid: &str, oldstr: &str, newstr: &str) -> io::Result<()> {
    assert!(oldstr.len() >= newstr.len());
    let maps_file = read_to_string(format!("/proc/{}/maps", pid))?;
    let line = maps_file
        .lines()
        .find(|x| x.contains("[heap]"))
        .expect("Couldn't find heap in /proc/<pid>/maps");
    if let [start, end, ..] = line
        .split(&[' ', '-'][..])
        .collect::<Vec<_>>()
        .iter()
        .take(2)
        .map(|x| usize::from_str_radix(x, 16).unwrap())
        .collect::<Vec<_>>()[..]
    {
        let mut mem_file = OpenOptions::new()
            .read(true)
            .write(true)
            .open(format!("/proc/{}/mem", pid))?;
        let mut heap = Vec::new();
        mem_file.seek(SeekFrom::Start(start as u64))?;
        {
            let mem_ref = Read::by_ref(&mut mem_file);
            mem_ref.take((end - start) as u64).read_to_end(&mut heap)?;
        }
        for (i, w) in heap.windows(oldstr.len()).enumerate() {
            if w == oldstr.as_bytes() {
                mem_file.seek(SeekFrom::Start((start + i) as u64))?;
                mem_file.write(newstr.as_bytes())?;
            }
        }
        Ok(())
    } else {
        panic!("Couldn't parse heap addresses");
    }
}
