{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var k,n,ky,h:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(k);
h:=0;
ky:=1;
while not(ky>=n) do
begin
inc(h);
ky:=ky+min(ky,k);
end;
write(h);
end.