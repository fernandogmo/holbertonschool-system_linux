#![allow(unused)]
use itertools::Itertools;
use std::{
    convert::{Into, TryInto},
    env::args,
    fs::{read_to_string, File, OpenOptions},
    io::{prelude::*, SeekFrom},
    str::FromStr,
    vec::Vec,
};

fn main() {
    if let Some((_, pid, oldstr, newstr)) = args().collect_tuple() {
        read_write_heap(pid, oldstr, newstr);
    } else {
        println!("Usage: ./read_write_heap <pid> <old-string> <new-string>");
    }
    // match args().skip(1).collect_tuple() {
    //     Some((pid, oldstr, newstr)) => read_write_heap(pid, oldstr, newstr),
    //     _ => println!("Usage: ./read_write_heap <pid> <old-string> <new-string>"),
    // };
}

fn read_write_heap(pid: String, oldstr: String, newstr: String) -> () {
    assert!(oldstr.len() >= newstr.len());
    let maps_file = read_to_string(format!("/proc/{}/maps", pid)).unwrap();
    let mut line = maps_file
        .lines()
        .find(|x| x.contains("[heap]"))
        .expect("Couldn't find heap in /proc/<pid>/maps");
    let (start, end) = line
        .split(' ')
        .nth(0)
        .expect("Couldn't parse heap entry in maps")
        .split('-')
        .collect_vec()
        .iter()
        .map(|x| usize::from_str_radix(x, 16).unwrap())
        .collect_tuple()
        .expect("Couldn't parse heap addresses");
    let mut mem_file = OpenOptions::new()
        .read(true)
        .write(true)
        .open(format!("/proc/{}/mem", pid))
        .unwrap();
    mem_file.seek(SeekFrom::Start(start as u64)).unwrap();
    let mut heap = Vec::new();
    Read::by_ref(&mut mem_file)
        .take((end - start) as u64)
        .read_to_end(&mut heap);
    for (i, w) in heap.windows(oldstr.len()).enumerate() {
        if w == oldstr.as_bytes() {
            mem_file.seek(SeekFrom::Start((start + i) as u64));
            mem_file.write(newstr.as_bytes());
        }
    }
    // let slice = &[0u8];
    // for i in 0..=heap.len() - oldstr.len() {
    //     if heap[i..].starts_with(oldstr.as_bytes()) {
    //         mem_file.seek(SeekFrom::Current(i as i64));
    //         mem_file.write()
    //     }
    // }
}
