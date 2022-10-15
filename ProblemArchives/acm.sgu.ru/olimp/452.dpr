{$APPTYPE CONSOLE}
uses
  SysUtils;
var n,i:integer;
    a:array[1..1000] of integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do read(a[i]);
for i:=2 to n do
if a[1]>=a[i] then inc(a[1])
else break;
write(a[1]);
end.