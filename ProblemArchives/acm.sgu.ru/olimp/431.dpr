{$I-,O+,R-,Q-}
{$APPTYPE CONSOLE}
var a,b,c,d,min:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a,b,c,d);
if a>b then min:=b
  else min:=a ;
if c<min then min:=c;
if d<min then min:=d;
write(min);
end.
 