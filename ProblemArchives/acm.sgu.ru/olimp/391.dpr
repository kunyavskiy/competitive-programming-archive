{$APPTYPE CONSOLE}
{$I-,O+,R-,Q-}
uses
  SysUtils,math;
var a1,a2,b1,b2:integer;
procedure swap( var a,b:integer);
var t:integer;
begin
t:=a;
a:=b;
b:=t;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a1,a2,b1,b2);
if a1<a2 then swap(a1,a2);
if b1<b2 then swap(b1,b2);
if (a1=b1) and(a2=b2) then write(0)
else if (a1=b1) or (a2=b2) or (a1=b2) or (a2=b1) then write(1)
else write(2);
end.