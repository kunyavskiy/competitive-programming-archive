s := File standardInput readLine asNumber
s0:=s
t := s
while (s>0,
t := if (s<t,s,t)
q := 1
for (i,2,t-1,
if (t%i==0,
q:=0
break
)
)
if (q==1,
t print
s := s-t
if (s!=0,"+" print)
,
t:=t-1
)

)
"=" print
s0 print
"\n" print

