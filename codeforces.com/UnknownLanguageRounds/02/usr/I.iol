s := File standardInput readLine asNumber
n := s
q := 1
q2 := 0
while (s>0,
t := s%10
s := (s-t)/10
if (n%t==0,q2:=1,q:=0)
)
if (q2==0,"upset" print,if(q==0,"happy" print,"happier" print))
