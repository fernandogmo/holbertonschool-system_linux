#!/usr/bin/env python3

from typing import List
import random
import sys

Row = List[float]

def midrow(n: int) -> Row:
    r = sorted([max(1.0, round(random.gauss(1.0, 50), 1))
               for i in range((n//2))])
    r += [r[-1] + 1]
    return r


def nextrow(r: Row) -> Row:
    return [max(0.1, round(r[0] - 0.1, 1))] + r[:-1]


def make_bottom(n: int) -> List[Row]:
    r = [midrow(n)]
    n = n // 2 + 1
    while (n := n - 1):
        r += [nextrow(r[-1])]
    return r


def fullrow(r: Row) -> Row:
    return r + r[:-1][::-1]


def make_gaussian_kernel(n: int):
    b = make_bottom(max(n, 3))
    return b[1:][::-1] + b


if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 5
    n = 2 * (n // 2) + 1
    print(n)
    k = make_gaussian_kernel(n)
    for r in k:
        fr = fullrow(r)
        fr_str = ""
        for x in fr:
            tens = 2 if int(x) // 10 else 1
            width = 4 - tens
            fr_str += f"{x:.1f}" + " " * width
        print(fr_str)
