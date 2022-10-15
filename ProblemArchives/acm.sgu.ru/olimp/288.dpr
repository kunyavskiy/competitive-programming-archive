{$APPTYPE CONSOLE}
uses math;
type int=longint;
var n,i,x0:int;
    x: array[0..199] of int;
procedure swap(var a,b:int);
var t:int;
begin
t:=a;
a:=b;
b:=t ;
end;
procedure puz (var a:array of int);
var j,l:int;
begin
for l:=0 to n-1 do
  for j:=l to n-1 do
    if a[j]>a[l] then swap(a[j],a[l]);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(x0);
for i:=1 to n do
read(x[i-1]);
puz(x);
write(min(abs(x0-x[0]),abs(x0-x[n-1]))+x[0]-x[n-1]);
end.