import sys

while True:
    print "GETDEGREE"
    sys.stdout.flush()
    n = int(raw_input())
    if (n == -1):
        break
    n -= 1
    print "EVAL 21"
    sys.stdout.flush()
    x = int(raw_input())
    a = []
    p = 1
    for i in xrange(n + 1):
        x += p * 10
        p *= 21
    for i in xrange(n + 1):
        a.append(x % 21)
        x -= x % 21
        x /= 21
    print "GUESS",
    sys.stdout.flush()
    for i in xrange(n + 1):
        print a[n - i] - 10,
        sys.stdout.flush()
    print
    sys.stdout.flush()
    yes = raw_input()
print "QUIT"
sys.stdout.flush()