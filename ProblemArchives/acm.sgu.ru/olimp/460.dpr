{$apptype console}
type aray=array[1..350] of shortint;
var m2,n2,s:aray;
		j,m,n:integer;
    q:boolean;
procedure double (var a:aray);
var i,b:integer;
begin
b:=0;
for i:=350 downto 1 do
begin
a[i]:=a[i]*2+b;
b:=a[i] div 10;
a[i]:=a[i] mod 10;
end;
end;
procedure sum (a,c:aray; var d:aray);
var i,b:integer;
begin
b:=0;
for i:=350 downto 1 do
begin
d[i]:=a[i]+c[i]+b;
b:=d[i] div 10;
d[i]:=d[i] mod 10;
end;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
read(m);
m2[350]:=1;
n2[350]:=1;
for j:=1 to m do
double(m2);
for j:=1 to n do
double(n2);
sum(m2,n2,s);
if s[350]>=2 then s[350]:=s[350]-2
else
begin
s[350]:=s[350]+8;
j:=349;
while s[j]=0 do
begin
s[j]:=9;
dec(j);
end;
s[j]:=s[j]-1;
end;
q:=false;
for j:=1 to 350 do
if not(s[j]=0) or (q=true) then
begin
q:=true;
write(s[j]);
end
end.