{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var a,v:array[1..100] of integer;
    n,i,p,per,j:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
begin
read(v[i]);
readln(a[i]);
end;
for i:=1 to n do
begin
read(p);
for j:=p+1 to n do
begin
per:=min(a[p],v[j]-a[j]);
a[j]:=a[j]+per;
a[p]:=a[p]-per;
if a[p]=0 then break         ;
end;
end;
for i:=1 to n do write(a[i],' ');
end.