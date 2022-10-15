{$APPTYPE CONSOLE}
{$O-}
uses
  SysUtils,math;
var n,i,q,b,k:integer;
    a:array[1..2000] of integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
readln(q) ;
fillchar(a,sizeof(a),0);
for i:=1 to n do
begin
read(b);
inc(a[b]);
end;
k:=0;
if q mod 2=1 then
for i:=1 to q div 2 do
k:=k+min(a[i],a[q-i])
else
begin
for i:=1 to (q div 2)-1 do
k:=k+min(a[i],a[q-i]);
k:=k+(a[q div 2] div 2);
end;
write(k);
end.