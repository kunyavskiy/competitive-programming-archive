{$APPTYPE CONSOLE}
{$O+}
uses
  SysUtils;
var a:array[1..1000,1..2] of integer;
    s,e,n,m,k,max,j,l,i,t:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(m);
for i:=1 to n do
begin
read(a[i,1]);
read(a[i,2]);
a[i,2]:=a[i,2]+a[i,1];
end;
max:=0;
t:=0;
for i:=1 to n do
for j:=1 to 2 do
begin
k:=0;
s:=a[i,j];
e:=a[i,j]+m;
for l:=1 to n do
if ((s<=a[l,1]) and (e>=a[l,2])) or ((s<=a[l,2])and (s>=a[l,1])) or ((e<=a[l,2])and (e>=a[l,1])) then inc(k);
if k>max then
begin
max:=k;
t:=a[i,j];
end;
end;
write(t)
end.