s := File standardInput readLine
n := s size
best := ""
kol := -1

for (i,0,n-1,
	for (j,i+1,n,
		t := s slice(i,j)
		cur := 0
		len := j-i
		for (k,0,n-len,
		   if (s slice(k,k+len) == t,cur:=cur+1)
		)		
		if ((cur > kol) or ((cur == kol) and ((best size < t size) or ((best size == t size) and (best < t)))),
		   best := t
		   kol := cur
		)
	)
)
best print
