n = (int)(raw_input())


def gena(x):
    a = [1,2]

    for i in range(1,2**x,2):
       a.append(i)

    n0 = n

    while n0 > 1:
       a.append(n0)
       if n0 % 2 == 0:
           n0 = n0 / 2
       else:
           n0 = n0 - n0%(2**x)

    a = list(set(a));
    a.sort()

    while a[len(a) - 1] > n:
       a = a[:-1]
    return a

a = [1] + [0] * 500
for i in range(1,9):
   y = gena(i)
   if (len(y) < len(a)):
      a = y



print len(a)-1
for i in range(1,len(a)):
    q = False
    for j in range(i-1,-1,-1):
       for k in range(j,-1,-1):
           if (a[j] + a[k] == a[i]):
               print k,j
               q = True
               break
       if q:
           break
    assert(q)