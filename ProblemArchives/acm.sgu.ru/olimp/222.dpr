var a:array[0..51,0..51] of integer;
		n,m,i,j,k:integer;
		c:char;
		q:boolean;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
readln(m);
fillchar(a,sizeof(a),0);
for i:=0 to m+1 do
begin
a[0,i]:=2;
a[n+1,i]:=2;
end;
for i:=0 to n+1 do
begin
a[i,0]:=2;
a[i,m+1]:=2;
end;
for i:=1 to n do
begin
	for j:=1 to m do
	begin
		read(c);
		if c='.' then a[i,j]:=2;
	end;
readln;
end;
for i:=1 to n do
	for j:=1 to m do
		begin
		q:=a[i-1,j-1]=2;
		q:=(a[i-1,j]=2) or (q=true);
		q:=(a[i-1,j+1]=2) or (q=true);
		q:=(a[i,j-1]=2) or (q=true);
		q:=(a[i,j+1]=2) or (q=true);
		q:=(a[i+1,j-1]=2) or (q=true);
		q:=(a[i+1,j]=2) or (q=true);
		q:=(a[i+1,j+1]=2) or (q=true);
	 if not(a[i,j]=2) and (q=true) then
	 a[i,j]:=1;
	 end;
k:=0;
for i:=1 to n do
	for j:=1 to m do
	if a[i,j]=0 then inc(k);
write(k,'0000')
end.
