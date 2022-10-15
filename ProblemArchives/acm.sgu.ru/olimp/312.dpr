{$APPTYPE CONSOLE}
type int=longint;
var n,p,i:int;
    a:array[1..1000] of int;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
read(a[i]);
p:=n*2+a[1]+a[n];
for i:=1 to n-1 do
p:=p+abs(a[i]-a[i+1]);
write(p);
end.