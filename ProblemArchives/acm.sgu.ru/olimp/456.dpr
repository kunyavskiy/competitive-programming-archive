{$APPTYPE CONSOLE}
uses
  SysUtils;
var m,n,k,i,min:integer;
    ka:array[1..100] of integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(m,n,k);
i:=1;
while i<=m do
begin
if i<=n then ka[i]:=200*(n-i)
else ka[i]:=100*(i-n);
i:=i+k;
end;
min:=maxlongint;
for i:=1 to n do
if ka[i]<min then min:=ka[i];
write(min);
end.