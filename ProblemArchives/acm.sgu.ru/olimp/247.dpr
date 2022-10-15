var a:array[1..1000] of integer;
		i,n,m,num,max,s,j:longint;
function del(a:integer):integer;
var k,j:integer;
begin
k:=0;
for j:=1 to trunc(sqrt(a)) do
if a mod j=0 then inc(k);
k:=k*2;
if trunc(sqrt(a))=sqrt(a) then dec(k);
del:=k;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
for i:=1 to n do a[i]:=del(i);
read(m);
s:=0;
num:=0;
max:=0;
for i:=1 to m do
begin
max:=0;
num:=0;
for j:=1 to n do
if a[j]>max then
begin
num:=j;
max:=a[j];
end;
s:=s+num;
a[num]:=0;
end;
write(s);
end.



