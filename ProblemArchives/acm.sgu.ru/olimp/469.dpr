{$APPTYPE CONSOLE}
{$O+}
uses
  SysUtils,math;
type aray=array[1..10]of integer;
var n,m,i,l:integer;
    a,b:aray;
    q:boolean;
procedure inttomas (d:integer;var c:aray);
var i:integer;
begin
i:=l ;
while not (d=0) do
begin
c[i]:=d mod 10;
dec(i);
d:=d div 10;
end;
end;
function inst(s:string):boolean;
var i:integer;
begin
inst:=false;
for i:=1 to length(s) do
if not(s[i]='9') then exit;
inst:=true;
end;
function p(c:aray;q:boolean):integer;
var r,i:integer;
begin
r:=1;
for i:=1 to l-1 do
r:=r*c[i];
if q then r:=r*c[l];
p:=r;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
l:=length(inttostr(n));
inttomas(n,a);
for i:=2 to l do
b[i]:=9;
b[1]:=a[1]-1;
q:=true;
if b[1]=0 then begin b[1]:=9; b[l]:=0; q:=false end;
m:=p(b,q);
for i:=2 to l do
begin
inc(b[i-1]);
b[i]:=a[i]-1;
m:=max(m,p(b,true));
end;
m:=max(m,p(a,true));
write(m)
end.