{$APPTYPE CONSOLE}

uses
  SysUtils;

var t,t1,t2:integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(t1,t2,t);
  if t1>t2 then swap(t1,t2);
  if (t1<=t) and (t<=t2) then write('YES')
  else write('NO');
end.