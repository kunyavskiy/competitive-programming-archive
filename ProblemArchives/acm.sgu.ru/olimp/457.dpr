{$APPTYPE CONSOLE}
uses
  SysUtils;
var  a,b:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a,b);
if b=8 then
case a of
0,4,5:write('YES');
else write('NO');
end
else write('NO')
end.