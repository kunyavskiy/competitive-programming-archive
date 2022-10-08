#!/usr/bin/python

x = [2] * 58 + 4 * [3]
print(sum(x))

s = 0
while len(x) > 1:
   s += x[0] + x[1]
   x = x[2:] + [x[0] + x[1]]
   x.sort()
   print(x)
print(s)
