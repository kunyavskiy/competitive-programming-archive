#!/usr/bin/python

from random import *

n = 1000
p = 123456
a = [randint(0, p) for i in range(n)]

def solve1():
  global p
  dp = [1, 1, 1]
  for i in range(3, len(a)):
    dp.append((dp[i - 1] + dp[i // 3] + a[i]) % p)
  return dp[-1]

def solve2():
  global p
  dp = [0, 1, 1]
  sa = [0, 1, 1]
  sdp = [0, 1, 2]
  for i in range(3, len(a)):
    sa.append((sa[-1] + a[i]) % p)
    dp.append((3 * sdp[i // 3] + sa[i] - (2 - i % 3) * dp[i // 3]) % p)
    sdp.append((sdp[-1] + dp[i]) % p)
  return dp[-1]

assert solve1() == solve2()
