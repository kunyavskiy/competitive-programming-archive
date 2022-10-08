#!/usr/bin/python2

from sys import stdin


inp = open("a.in");


def solve():
   s, n = inp.readline().split()
   s = ''.join(sorted(list(s)))
   n = int(n) - 1
   l = len(s)
   if l == 1 :
      print s * (n+1)
      return
   anslen = 1
   while l ** anslen < n:
       n -= l ** anslen
       anslen += 1
   ans = ''
   for j in range(anslen)[::-1]:
      ans += s[n / l ** j]
      n %= l ** j
   print ans


tst = int(inp.readline())
for i in range(tst):
    print ('Case #%d:' % (i + 1)),
    solve()