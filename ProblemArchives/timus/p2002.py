#!/usr/bin/python

from sys import stdin

users = dict()
logged = set();


for x in stdin.readlines()[1:]:
    a = x.split()
    if a[0] == 'register':
       if a[1] in users:
           print 'fail: user already exists'
       else:
           print 'success: new user added'
           users[a[1]] = a[2]
    elif a[0] == 'login':
        if a[1] not in users:
           print 'fail: no such user'
        elif users[a[1]] != a[2]:
           print 'fail: incorrect password'
        elif a[1] in logged:
           print 'fail: already logged in'
        else:
           print 'success: user logged in'
           logged.add(a[1])
    else:
         if a[1] not in users:
           print 'fail: no such user'
         elif a[1] not in logged:
           print 'fail: already logged out'
         else:
           print 'success: user logged out'
           logged.remove(a[1])
