{$APPTYPE CONSOLE}
uses
  SysUtils;

var i,j,k,n,num,s:integer;
    a:array[1..7500] of integer;
    m:real;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(k);
for i:=1 to n do read(a[i]);
for i:=1 to n-k+1 do
begin
s:=0;
for j:=i to i+k-1 do s:=s+a[j];
if m<s/k then
begin
num:=i;
m:=s/k;
end;
end;
writeln(m:0:3);
writeln(num);
end.