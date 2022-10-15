#!/usr/bin/python

from sys import stdin


def solve():
    stdin.readline()
    x = map(int, stdin.readline().split())
    l, r = map(int, stdin.readline().split())
    l, r = l-1, r-1

    if l == r:
        a = sum(x[:l])
        b = sum(x[l+1:])
        print max(a, b) + x[l], min(a, b)
        return
    if l > r:
       x = x[::-1]
       l = len(x) - l - 1
       r = len(x) - r - 1
    a = sum(x[:l+1])
    b = sum(x[r:])
    x = x[l+1:r]
    a = a + sum(x[:(len(x)+1)/2])
    b = b + sum(x[(len(x)+1)/2:])
    print a, b

solve() 