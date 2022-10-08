#!/usr/bin/python

from random import *

def med(x):
  x = sorted(x)
  if len(x) % 2 == 0:
    return (x[len(x) / 2 - 1] + x[len(x) / 2]) / 2.0
  return x[len(x) / 2]

def avg(x):
  return sum(x) * 1.0 / len(x)

def calc(x):
  return avg(x) - med(x)




def go(x, y):
  global best
  if not x:
    if y:
      cx = calc(best)
      cy = calc(y)
      if cx < cy or (cx == cy and len(y) < len(best)) :
        best = y
    return

  go(x[1:], y)
  go(x[1:], y + x[:1])

best = x = sorted([randint(1, 1000) for i in range(15)])
go(x, [])

print x
print sorted(best), calc(best)
assert(len(best) % 2 != 0)

l = len(best)
x = sorted(x)
y = x[:l/2 + 1] + x[-l/2 + 1:]
print y, calc(y)
assert(y == best)
