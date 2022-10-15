{$APPTYPE CONSOLE}
var a,b,x,y:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a);
read(b);
read(x);
read(y);
if ((a>=x) and (b>=y)) or((a>=y) and(b>=x)) or (x+y<=a) or (x+y<=b) then write('YES')
else write('NO');
end.