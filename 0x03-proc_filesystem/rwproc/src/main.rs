// #![allow(unused)]
use std::fs::{read_to_string, OpenOptions};
use std::io::{prelude::*, Read, SeekFrom};
use std::vec::Vec;
use std::{convert::TryInto, env::args};

fn main() -> std::io::Result<()> {
    if let [_, pid, oldstr, newstr] = &args().collect::<Vec<_>>()[..] {
        read_write_heap(pid, oldstr, newstr)?;
    } else {
        eprintln!("Usage: ./read_write_heap <pid> <old-string> <new-string>");
    }
    Ok(())
}

fn read_write_heap(pid: &str, oldstr: &str, newstr: &str) -> std::io::Result<()> {
    assert!(oldstr.len() >= newstr.len());
    let maps_file = read_to_string(format!("/proc/{}/maps", pid))?;
    let line = maps_file
        .lines()
        .find(|x| x.contains("[heap]"))
        .expect("Couldn't find heap in /proc/<pid>/maps");
    // TODO: add some tests
    // // let line = "123-r21 qw er ty";
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

    // TODO: exit with error if oldstr not found. use `filter_map`?
    for (i, w) in heap.windows(oldstr.len()).enumerate() {
        if w == oldstr.as_bytes() {
            mem_file.seek(SeekFrom::Start((start + i) as u64))?;
            mem_file.write(newstr.as_bytes())?;
        }
    }
    Ok(())
}
