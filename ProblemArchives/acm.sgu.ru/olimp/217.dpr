type int=longint;
var a,n,i:int;
		ab:array[1..10] of int;
procedure inttomass (c:int; var d:array of int;var ras:int);
var j,e:int;
begin
e:=c;
ras:=0;
while not (e=0) do
begin
ras:=ras+1;
e:=e div 10;
end;
for j:=1 to ras do
begin
d[ras-j]:=c mod 10;
c:=c div 10;
end
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
n:=0;
inttomass(a,ab,n);
for i:=2 to n do
begin
ab[i]:=ab[i]-ab[i-1];
if ab[i]<0 then ab[i]:=ab[i]+10;
end;
for i:=1 to n do write(ab[i]);
end.



