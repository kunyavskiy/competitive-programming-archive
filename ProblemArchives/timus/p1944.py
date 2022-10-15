#!/usr/bin/python
from sys import stdin

tmp = map(int,stdin.read().split())
n = tmp[0]
x = tmp[2::2] + [0]
y = tmp[1::2] + [0]

for i in range(n):
   x[i] *= -1
#   y[i] *= -1

minx = reduce(min,x)
maxx = reduce(max,x)
miny = reduce(min,y)
maxy = reduce(max,y)

ans = [list('.'*(maxy - miny+1)) for _ in range(maxx-minx+1)]
                 
         
for i in range(minx,maxx+1):
	ans[i-minx][0-miny] = '|'


for i in range(miny,maxy+1):
	ans[0-minx][i-miny] = '-'


ans[0-minx][0-miny] = '+'

x = x[:-1]
y = y[:-1]

for i in range(len(x)):
    ans[x[i]-minx][y[i]-miny] = '*'
                         

print '\n'.join([''.join(i) for i in ans])