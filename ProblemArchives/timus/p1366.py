#!/usr/bin/python

import sys

a = 1
res = 1
n = int(sys.stdin.read())

for i in range(1, n+1):
	res = i*res + (-1)**i

sys.stdout.write(str(res)+'\n')