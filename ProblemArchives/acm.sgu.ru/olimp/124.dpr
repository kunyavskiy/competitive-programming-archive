var n,i,j,max:integer;
		a:array[1..100]  of integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
for i:=1 to n do
read(a[i]);
for i:=1 to 3 do
begin
 max:=a[1];
 for j:=1 to n do
	if a[j]>max then max:=a[j];
 for j:=1 to n do
	if a[j]=max then a[j]:=0;
 write(max,' ');
end;
end.