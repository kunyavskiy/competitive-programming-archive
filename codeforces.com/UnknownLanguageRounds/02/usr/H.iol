s := File standardInput readLine
if (s at(0) asCharacter == "-",
   s := s slice(1)
   "-" print
   )  
while (s size != 1 and s at(0) asCharacter == "0",s:=s slice(1))
t:=""
for (i,(s size -1),0,-1,t := t .. s at(i) asCharacter)
s:=t
while (s size != 1 and s at(0) asCharacter == "0",s:=s slice(1))
s print
"\n" print 



