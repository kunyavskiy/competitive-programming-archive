#!/usr/bin/python

from sys import stdin

def solve(s):
    x = s.split(",")
    if (len(x) == 2):
        return solve(x[0])+','+solve(x[1])
    first = s.split("{")[1].split("}")[0]
    second = s.split("(")[1].split(")")[0]
    third = s.split("[")[1].split("]")[0]
    join = s.split("{")[0].split("(")[0].split("[")[0]
    return join + first + ' ' + second + ' '+ third

x = solve(stdin.readline())
x = x[:1].upper() + x[1:].lower()
print x
