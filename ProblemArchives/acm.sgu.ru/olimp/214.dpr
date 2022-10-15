var a,b:array[1..1000] of longint;
		n,s,l,i,j:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(n);
s:=0;
l:=0;
for i:=1 to n do readln(a[i]);
b[1]:=a[1];
for i:=2 to n do b[i]:=b[i-1]+a[i];
for i:=1 to n do
begin
for j:=n downto i do
if b[j]=0 then
if (j-i+1)>l then
begin
l:=j-i+1;
s:=i;
end;
for j:=i to n do b[j]:=b[j]-a[i];
end;
write(l,' ',s);
end.