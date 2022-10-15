var a,b:array [1..1000] of longint;
		i,j,n,num,min:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
for i:=1 to n do
read(b[i]);
for i:=1 to n do
begin
 min:=b[i];
 num:=i;
 for j:=i to n do
	if b[j]<min then
	begin
	 min:=b[j];
	 num:=j;
	end;
 b[num]:=b[i];
 b[i]:=min;
end;
a[1]:=b[1];
for i:=2 to n do
a[i]:=b[i]-b[i-1];
for i:=1 to n do write(a[i],' ');
end.