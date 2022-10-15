{$APPTYPE CONSOLE}
{$I-,O+,R-,Q-}
uses
  SysUtils;
var n,j,i,k:longint;
    a:array[1..8] of longint;
    c:string;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
k:=0;
i:=1;
while i<=n do
begin
c:=inttostr(i);
for j:=1 to length(c) do
case c[j] of
'1':a[j]:=1;
'2':a[j]:=2;
'3':a[j]:=3;
'4':a[j]:=4;
'5':a[j]:=5;
'6':a[j]:=6;
'7':a[j]:=7;
'8':a[j]:=8;
'9':a[j]:=9;
'0':a[j]:=0;
end;
for j:=1 to length(c)-1 do
if a[j]>a[j+1] then a[j+1]:=a[j];
for j:=1 to length(c) do
case a[j] of
1:c[j]:='1';
2:c[j]:='2';
3:c[j]:='3';
4:c[j]:='4' ;
5:c[j]:='5';
6:c[j]:='6';
7:c[j]:='7';
8:c[j]:='8';
9:c[j]:='9';
0:c[j]:='0';
end;
i:=strtoint(c);
if i<=n then inc(k);
inc(i);
end;
write(k);
end.