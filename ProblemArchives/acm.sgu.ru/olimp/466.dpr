{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var  c:integer;
procedure koren (var a:integer);
var b:integer;
begin
if a<10 then exit;
b:=a;
a:=0;
while b>0 do
begin
a:=a+b mod 10;
b:=b div 10;
end;
koren(a);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(c);
koren(c);
write(c);
end.