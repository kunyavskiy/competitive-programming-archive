{$APPTYPE CONSOLE}
uses
  SysUtils;
type int=1..1152921504606846976;
var n,j,i:integer;
    a:array[1..60] of int;
function stepen(a:integer):int;
var b:int;
    j:integer;
begin
b:=1;
for j:=1 to a do b:=b*2;
stepen:=b;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
begin
a[i]:=stepen(i);
for j:=1 to i-1 do
if i mod j=0 then a[i]:=a[i]-a[j]
end;
write(a[n])
end.