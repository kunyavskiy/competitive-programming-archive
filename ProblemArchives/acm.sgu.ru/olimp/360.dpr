{$APPTYPE CONSOLE}
{$I-,O+,R-,Q-}
uses
  SysUtils,math;
var a:array[1..50,1..50] of integer;
    b:array[1..50] of integer;
    strmax,stlmin,n,m,j,i:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n,m);
fillchar(b,sizeof(b),0);
for i:=1 to n do
  for j:=1 to m do
    read(a[i,j]);
for i:=1 to n do
  begin
 b[i]:=a[i,1];
 for j:=1 to m do
 b[i]:=min(b[i],a[i,j]);
 end;
 strmax:=b[1];
 for i:=2 to n do
 strmax:=max(strmax,b[i]);
fillchar(b,sizeof(b),0);
for j:=1 to m do
  begin
 b[j]:=a[1,j];
 for i:=1 to n do
 b[j]:=max(b[j],a[i,j]);
 end;
 stlmin:=b[1];
 for i:=2 to m do
 stlmin:=min(stlmin,b[i]);
 write(min(strmax,stlmin),' ',max(strmax,stlmin));
end.