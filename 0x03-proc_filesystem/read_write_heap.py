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
    try:
        heap_start = heap_end = None
        with open("/proc/{}/maps".format(pid), 'r') as mappings:
            for line in mappings:
                if '[heap]' in line:
                    heap_start, heap_end = line.split(maxsplit=1)[0].split("-")
        with open("/proc/{}/mem".format(pid), 'rb+') as mem:
            heap_start = int(heap_start, 16)
            heap_end = int(heap_end, 16)
            mem.seek(heap_start)
            heap = mem.read(heap_end - heap_start)
            offset = heap.find(bytes(oldstr, "ASCII"))
            if offset != -1:
                mem.seek(heap_start + offset)
                mem.write(bytes(newstr + '\0', "ASCII"))
            else:
                exit(1)
    except Exception as e:
        print("{}:".format(type(e).__name__),
              e, file=sys.stderr)
        exit(1)


if __name__ == '__main__':
    try:
        _, pid, oldstr, newstr = sys.argv
        if len(oldstr) < len(newstr):
            raise ValueError("<new-string> cannot be longer than <old-string>")
        read_write_heap(pid, oldstr, newstr)
    except ValueError as e:
        print(e, "Usage: read_write_heap.py <pid> <old-string> <new-string>",
              sep='\n', file=sys.stderr)
        exit(1)
    except Exception as e:
        print("You shouldn't be seeing this.\n",
              "DM me on Twitter @fernandogmo",
              e, file=sys.stderr)
        exit(1)

# %%
