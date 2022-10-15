{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var n,i,j,a1,a2,a3,b1,b2,b3:integer;
    a,b:array[1..4] of integer;
    res:boolean;
procedure swap (var a,b:integer);
var t:integer;
begin
t:=a;
a:=b;
b:=t;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for j:=1 to n do
begin
read(a1,b1,a2,b2,a3,b3);
if a3<b3 then swap(a3,b3);
a[1]:=a1+a2;
b[1]:=max(b1,b2);
if a[1]<b[1] then swap(a[1],b[1]);
a[2]:=b1+b2;
b[2]:=max(a1,a2);
if a[2]<b[2] then swap(a[2],b[2]);
a[3]:=a1+b2;
b[3]:=max(b1,a2);
if a[3]<b[3] then swap(a[3],b[3]);
a[4]:=b1+a2;
b[4]:=max(a1,b2);
if a[4]<b[4] then swap(a[4],b[4]);
res:=false;
for i:=1 to 4 do
if a[i]>a3 then res:=false or res
else if a[i]<=b3 then res:=true
  else res:=res or (b[i]<=b3);
if res=true then writeln(1) else writeln(0)
end;
end.