#!/usr/bin/python2

from sys import stdin


inp = open("b.in");

def solve2(m, p, team):
    now = team[:p]
    wait = team[p:]
    for _ in range(m):
        for j in now:
            j[2] += 1
        if wait:
            now.sort(key = lambda x: [x[2], x[1]], reverse = True)
            wait.sort(key = lambda x: [x[2], x[1]])
            temp = now[0]
            now[0] = wait[0]
            wait[0] = temp
    return [i[0] for i in now]

def solve():
    n,m,p = map(int, inp.readline().split())
    person = [ inp.readline().split() for i in range(n) ]
    for i in person:
       i[1] = int(i[1])
       i[2] = int(i[2])
    person.sort(key = lambda x : [x[1] , x[2]], reverse = True)
    for i in range(len(person)):
        person[i][1] = i
        person[i][2] = 0
    result = solve2(m, p, person[::2]) + solve2(m, p, person[1::2])
    result.sort()
    print ' '.join(result)

tst = int(inp.readline())
for i in range(tst):
    print ('Case #%d:' % (i + 1)),
    solve()