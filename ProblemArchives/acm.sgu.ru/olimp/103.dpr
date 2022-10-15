{$H+}
{$apptype console}
type int=longint;
var st:string;
i,p,k,s,l,f:int;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(st);
p:=0;
k:=0;
s:=0;
l:=0;
f:=0;
for i:=1 to length(st) do
case st[i] of
'P':p:=p+1;
'K':k:=k+1;
'S':s:=s+1;
'L':l:=l+1;
'F':f:=f+1;
end;
for i:=1 to p do
write('P');
for i:=1 to k do
write('K');
for i:=1 to s do
write('S');
for i:=1 to l do
write('L');
for i:=1 to f do
write('F');
end.



