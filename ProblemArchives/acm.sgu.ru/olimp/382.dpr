{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var h:array[1..1000] of integer;
    maxa,n,kolz,kole,i:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do read(h[i]);
maxa:=h[1];
kolz:=1;
for i:=2 to n do
if h[i]>maxa then
begin
inc(kolz);
maxa:=h[i];
end;
maxa:=h[n];
kole:=1;
for i:=n-1 downto 1 do
if h[i]>maxa then
begin
inc(kole);
maxa:=h[i];
end;
if kole>kolz then writeln(1)
else writeln(2);
write(max(kolz,kole));
end.