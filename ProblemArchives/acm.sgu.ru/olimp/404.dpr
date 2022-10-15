{$APPTYPE CONSOLE}
{$I-,O+,R-,Q-}
uses
  SysUtils;
var k,h1,m1,h2,m2:longint;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
readln(h1,m1);
read(h2,m2);
if h1>h2 then h2:=h2+24;
k:=h2-h1;
m1:=m1+k;
if m1>60 then m1:=m1-60;
if m1>m2 then m2:=m2+60;
k:=k+m2-m1;
write(k)
end.