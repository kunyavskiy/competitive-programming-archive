#!/usr/bin/python3

from sys import stdin

t = int(stdin.readline())
for _ in range(t):
    n, m = [int(i) for i in stdin.readline().split()]
    p2 = 1
    pp = 0
    while p2 < n:
        p2 <<= 1
        pp += 1
    ans = 0
    while n > 0:
        if (p2 - 1) * m >= n:
            p2 >>= 1
            pp -= 1
        else:
            c = min(m, n >> pp)
            n -= c << pp
            ans |= p2
    print(ans)