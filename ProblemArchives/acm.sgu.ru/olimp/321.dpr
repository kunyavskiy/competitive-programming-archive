{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var i,k,x,k1,x1,kmin,xmin:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(k);
read(x);
kmin:=maxlongint;
xmin:=maxlongint;
for i:=1 to k do
begin
read(k1);
kmin:=min(kmin,k1);
end;
for i:=1 to x do
begin
read(x1);
xmin:=min(xmin,x1);
end;
if kmin<xmin then write('RIGHT')
else write('WRONG');
end.