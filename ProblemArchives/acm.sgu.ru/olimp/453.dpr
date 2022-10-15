{$APPTYPE CONSOLE}
uses
  SysUtils;
type  int=integer;
       aray=array[1..50] of int;
var a,s,i:integer;
    s1:aray;
    q:boolean;
procedure umch (a1:aray;ch:int;var a3:aray);
var b,j:int;
begin
b:=0;
for j:=50 downto 1 do
begin
a3[j]:=a1[j]*ch+b;
b:=a3[j]div 10;
a3[j]:=a3[j] mod 10;
end;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a);
s:=a;
read(a);
s:=s+a;
a:=s;
fillchar(s1,sizeof(s1),0);
s1[50]:=a mod 10;
a:=a div 10;
s1[49]:=a mod 10;
s1[48]:=a div 10;
read(a);
for i:=1 to a-1 do
umch(s1,s,s1);
q:=false;
for i:=1 to 50 do
if not(s1[i]=0) or q then
begin
q:=true;
write(s1[i]);
end
end.