a:=0
b:=1
n := File standardInput readLine asNumber
t:=1
for (i,1,n,
t=b
b=a+b
a=t
)
b print
