n := File standardInput readLine asNumber
x := clone
y := x
for (ITER,1,n,
   s := File standardInput readLine strip
   if (s at(0) asCharacter == ";",continue)
   if (s at(0) asCharacter == "[",
      s := s slice(1,-1) strip
      x newSlot(s,clone)
      y = x getSlot(s)
      ,
      y newSlot((s split("=") at(0) strip),(s split("=") at(1) strip))
   )
)      



