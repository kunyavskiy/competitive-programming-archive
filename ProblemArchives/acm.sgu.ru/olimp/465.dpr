{$APPTYPE CONSOLE}
uses
  SysUtils;
var m,n,k,i,min:longint;
    ka:array[1..100] of longint;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(m,n,k);
i:=1;
fillchar(ka,sizeof(ka),40000);
while i<=m do
begin
if i<=n then ka[(i div k) +1]:=200*(n-i)
else ka[i]:=100*(i-n);
i:=i+k;
end;
min:=maxlongint;
for i:=1 to 100 do
if ka[i]<min then min:=ka[i];
write(min);
end.