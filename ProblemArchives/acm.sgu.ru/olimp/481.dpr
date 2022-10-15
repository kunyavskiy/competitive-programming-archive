{$APPTYPE CONSOLE}

uses
  Math;

const eps=0.00001;

var a,b,c,d,s1,s2:extended;
    n:integer;

function ocrug(a:extended):integer;
begin
  if a-trunc(a)<eps then result:=trunc(a) else
  if 1-a+trunc(a)<eps then result:=trunc(a)+1 else
    halt(1);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b);
  read(n);
  if n=4 then
      read(c,d);
  if n=3 then
    begin
      read(c,d);
      c:=min(c,d);
      d:=c;
    end;
  s1:=a*b;
  s2:=c*d;
  if n=3 then
    s2:=s2/2;
  a:=log2(s1/s2);
  n:=ocrug(a);
  write(n);
end.