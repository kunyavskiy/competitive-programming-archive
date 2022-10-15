{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var  a,b,c,s:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a,b,c);
s:=a+b+c;
if s mod 3=0 then
begin
s:=s div 3;
write(max(max(abs(s-a),abs(s-b)),abs(s-c)));
end
else write('IMPOSSIBLE');
end.