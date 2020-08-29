#!/usr/bin/python3
"""
[*] maps: /proc/<PID>/maps
[*] mem: /proc/<PID>/maps
[*] Found [heap]:
        pathname = [heap]
        addresses = 022fa000-0231b000
        permissions = rw-p
        offset = 00000000
        inode = 0
[*] Addr start [22fa000] | end [231b000]
[*] Found 'Holberton' at 10
[*] Writing 'Hello :o)' at 22fa010
"""

import sys


def read_write_heap(pid, oldstr, newstr):
    """ finds and replace string in heap of process """
    assert len(oldstr) >= len(newstr),\
        "<new-string> cannot be longer than <old-string>"
    with open("/proc/{}/maps".format(pid), 'r') as maps:
        line = next(x for x in maps if '[heap]' in x)
        h0, h1 = line.split(maxsplit=1)[0].split()
        h0, h1 = int(h0, 16), int(h1, 16)
    with open("/proc/{}/mem".format(pid), 'rb+') as mem:
        mem.seek(h0)
        heap = mem.read(h1 - h0)
        offset = heap.find(bytes(oldstr, "ascii"))
        assert offset != -1, "<old-string> not found"
        mem.seek(h0 + offset)
        mem.write(bytes(newstr + '\0', "ascii"))


if __name__ == '__main__':
    try:
        _, pid, oldstr, newstr = sys.argv
        read_write_heap(pid, oldstr, newstr)
    except AssertionError as e:
        print("{}: {}".format(_, e), file=sys.stderr)
        exit(1)
    except ValueError:
        print("Usage: read_write_heap.py <pid> <old-string> <new-string>",
              file=sys.stderr)
        exit(1)
    except Exception as e:
        print("You shouldn't be seeing this.",
              "DM me on Twitter @fernandogmo",
              "{}: {}".format(type(e).__name__, e),
              sep='\n', file=sys.stderr)
        exit(1)
