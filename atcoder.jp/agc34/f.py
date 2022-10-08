#!/usr/bin/python

from random import *

def ad(n):
  if n == 1:
    return [[1]]
    
  m = n // 2
  x = ad(m)
  y = [[x[i % m][j % m] * (-1 if i >= m and j >= m else 1) for j in range(n)] for i in range(n)]
  return y


def mult(x, y):
  assert(len(x[0]) == len(y))
  z = [[0 for i in range(len(y[0]))] for j in range(len(x))]
  for i in range(len(x)):
    for j in range(len(x[i])):
      for k in range(len(y[0])):
        z[i][k] += x[i][j] * y[j][k]
  return z

n = 4

A = [1, 2, 1, 2]
s = sum(A)

B = [[0 for i in range(n)] for j in range(n)]
for i in range(n):
   B[i][i] = s

print(A)

for j in range(1, n):
   for k in range(n):
      B[j][k] -= A[j ^ k]

print()
for i in range(n):
  print(B[i])

B = mult(mult(ad(n), B), ad(n))

print('AD')
for i in range(n):
  print(B[i])

for i in range(1, n):
  for j in range(n):
    B[i][j] -= B[0][j]

print()
for i in range(n):
  print(B[i])

B = mult([A], ad(n))

print()
for i in B:
  print(i)

B = mult(ad(n), [[n] for i in range(n)])

print()
for i in B:
  print(i)

