#!/usr/bin/python

x = [500, 1000, 1500, 2000, 2500, 3000]

for a in x:
   for b in x:
      for c in x:
         best = [a, b, c]
         worst = [a * 130.0 / 250.0, b * 130.0 / 250.0, c * 130.0 / 250.0]

         print best, worst
