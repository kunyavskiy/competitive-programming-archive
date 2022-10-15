from sys import *
def join(x):
    s=''
    for i in x:
        s=s+' '+i
    return s[1:]
while True:
  print 'GETDEGREE'   
  stdout.flush()
  d = int(raw_input())  
  if (d <= 0):
     print 'QUIT'
     stdout.flush()     
     break
  print 'EVAL',50
  stdout.flush()
  x = int(raw_input())
  c = [0] * d
  for i in range(0,d):
    y = x % 50
    while (y < -10):
        y = y + 50
    while (y > 10):
        y = y - 50
    assert((-10 <= y) and (y <= 10))
    c[i] = y
    x = x - y
    x = x // 50
  print 'GUESS '+join(map(str,c))  
  stdout.flush()
  s = raw_input()
  assert (s == 'YES')
  continue
    
