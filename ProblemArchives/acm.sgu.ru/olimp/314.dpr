{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var a1,a2,a3,a4,d1,d2,n,i:integer;
    q:boolean;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
begin
read(a1,a2,a3,a4,d1,d2);
q:=false;
q:=((a1<=d1) and (a2+a3+a4+2<=d2)) or q;
q:=((a2<=d1) and (a1+a3+a4+2<=d2)) or q;
q:=((a3<=d1) and (a2+a1+a4+2<=d2)) or q;
q:=((a4<=d1) and (a2+a3+a1+2<=d2)) or q;
q:=((a1+a2+1<=d1) and (a3+a4+1<=d2)) or q;
q:=((a1+a3+1<=d1) and (a2+a4+1<=d2)) or q;
q:=((a1+a4+1<=d1) and (a3+a2+1<=d2)) or q;
q:=((a1<=d2) and (a2+a3+a4+2<=d1)) or q;
q:=((a2<=d2) and (a1+a3+a4+2<=d1)) or q ;
q:=((a3<=d2) and (a2+a1+a4+2<=d1)) or q;
q:=((a4<=d2) and (a2+a3+a1+2<=d1)) or q;
q:=((a1+a2+1<=d2) and (a3+a4+1<=d1)) or q;
q:=((a1+a3+1<=d2) and (a2+a4+1<=d1)) or q;
q:=((a1+a4+1<=d2) and (a3+a2+1<=d1)) or q;
if q then writeln('YES')
else writeln('NO');
end;
end.