{$APPTYPE CONSOLE}
{$I-;O+;R-;Q-}
uses
  SysUtils;
var a:array[1..7500] of integer;
    b,n,k,i,c:integer;
function number(c:integer):integer;
var j:integer;
begin
j:=1;
while true do
if a[j]=c then break
else inc(j);
number:=j;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do read(a[i]);
read(b);
k:=0;
a[number(b)]:=0;
while not(b=0) do
begin
inc(k);
c:=a[b];
a[b]:=b;
b:=c
end;
write(k)
end.