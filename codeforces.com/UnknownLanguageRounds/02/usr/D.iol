s := File standardInput readLine

Acode := "A" at(0)
Zcode := "Z" at(0)
acode := "a" at(0)

downcase := method(c,
if(Acode <= c and c<=Zcode,(c-Acode+acode) asCharacter,c asCharacter)
)

stringset := method(s,i,c,
 (s slice(0,i)) .. c .. (s slice(i+1))
)




sz := s size
cnt := 0
for(i,0,sz-1,
if ((s at(i) asCharacter) == "\"",cnt:=cnt+1)
if (cnt%2 == 0,
	s:=stringset(s,i,downcase(s at(i)))
)
)


concat := method(x,y,x .. y)
reverse := method(x,
t := ""
sz := x size
for(i,0,sz-1, t:= (x at(i) asCharacter) .. t)
)

substr := method(x,a,b,c,
if (c == nil,c:=1)
t:=""
id:=a-1
while ((id<b) and (id < (x size)),
t:=t .. (x at(id) asCharacter)
id:= id + c
)
t
)


"\"" print
(("#{" .. s .. "}") interpolate) print
"\"" print

