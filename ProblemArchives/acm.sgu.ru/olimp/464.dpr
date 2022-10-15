{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var  n,m,t,k,p:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n,m,t,k);
p:=0;
m:=n*60+m+5;
while m+t<=720 do
begin
m:=m+t+k;
inc(p);
end;
write(p);
end.