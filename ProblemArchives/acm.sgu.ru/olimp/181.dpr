{$APPTYPE CONSOLE}
uses
 SysUtils,math;
var n,r,f:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n,r);
f:=max(1,2*n);
write(f,' ',((4*pi/3)*sqr(r)*r)/f:0:7,' ',((4*pi*sqr(r))/f+(pi*r*r)*ord(f<>1)):0:7);
end.