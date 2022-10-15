{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

var q,m,n,p,i,j:integer;
    okt:boolean;

function ok (a:integer; b:real):boolean;
var c:integer;
begin
  if b<>trunc(b) then begin ok:=false; exit; end;
  c:=trunc(b);
  ok:=(min(a,c)<=min(n,m)) and (max(a,c)<=max(m,n))
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(q);
  for i:=1 to q do
    begin
      read(n,m,p);
      okt:=false;
      for j:=1 to trunc(sqrt(p)) do
       if ok(j,p/j) then
         begin
         okt:=true;
         break;
         end;
       if okt then writeln('Yes')
       else writeln('No');
    end;
end.