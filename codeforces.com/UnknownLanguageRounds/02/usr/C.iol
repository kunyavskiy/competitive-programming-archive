n := File standardInput readLine asNumber
ch := 0
nch := 0
i:=1
while (i<=n,
if (n%i==0,nch=nch+1)
i=i+2
)
i=2
while (i<=n,
if (n%i==0,ch=ch+1)
i=i+2
)
if (nch == ch, "yes\n" print,"no\n" print)


