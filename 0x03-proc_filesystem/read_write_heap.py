#!/usr/bin/python3
"""
Finds a string in the heap of a running process and replaces it.

Usage: read_write_heap.py pid search_string replace_string
    where pid is the pid of the running process and strings are ASCII.
    The script should look only in the heap of the process.
    Output: you can print whatever you think is interesting
    On usage error, print error message on stdout and exit with status code 1
"""

import sys


def read_write_heap(pid, oldstr, newstr):
    """ finds and replaces string in heap of process """
    assert len(oldstr) >= len(newstr),\
        "<new-string> cannot be longer than <old-string>"
    with open("/proc/{}/maps".format(pid), 'r') as maps:
        line = next(x for x in maps if '[heap]' in x)
        h0, h1 = line.split(maxsplit=1)[0].split("-")
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
