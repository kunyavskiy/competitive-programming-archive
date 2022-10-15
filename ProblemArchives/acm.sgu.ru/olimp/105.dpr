type aray=array[1..7] of integer;
var j,n,m:longint;
		na,ma:aray;
		q:boolean;
procedure double (var a,c:aray);
var i,b:integer;
begin
b:=0;
for i:=7 downto 1 do
begin
a[i]:=a[i]+c[i]+b;
b:=a[i] div 2;
a[i]:=a[i] mod 2;
end;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n,m);
j:=7;
while n>0 do
begin
na[j]:=n mod 10;
n:=n div 10;
dec(j);
end;
j:=7;
while m>0 do
begin
ma[j]:=m mod 10;
m:=m div 10;
dec(j);
end;
double(na,ma);
for j:=1 to 7 do
if not(na[j]=0) or (q=true) then
begin
write(na[j]);
q:=true;
end;
end.