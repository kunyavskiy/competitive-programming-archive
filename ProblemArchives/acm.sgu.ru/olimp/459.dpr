{$APPTYPE CONSOLE}
uses
  SysUtils,math;
type aray=array[1..100000] of integer;
var pr,po:aray;
    num,n,m,i,maxc,ipr,ipo:integer;
    c:array[1..10000] of integer;
procedure QSort(left, right : integer;var a:aray);
var m, i, j, t : integer;
begin
  m := a[(left+right) div 2];
  i := left; j := right;
  repeat
    while a[i] < m do inc(i); {первый while}
    while a[j] > m do dec(j); {второй while}
    if i <= j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j,a);
  if i < right then QSort(i, right,a);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do read(pr[i]);
read(m);
for i:=1 to m do read(po[i]);
qsort(1,n,pr);
qsort(1,m,po);
maxc:=0;
num:=0;
ipr:=1;
ipo:=1;
repeat
if c[po[ipo]]=0 then
begin
while (pr[ipr]<=po[ipo]) and (ipr<=n) do inc(ipr);
c[po[ipo]]:=min(m-ipo+1,ipr-1)*po[ipo];
inc(ipo);
end
else inc(ipo)
until ipo>m;
for i:=1 to 10000 do
if c[i]>maxc then
begin
maxc:=c[i];
num:=i;
end;
write(num)
end.