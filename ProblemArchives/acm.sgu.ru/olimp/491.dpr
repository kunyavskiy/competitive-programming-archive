{$APPTYPE CONSOLE}
type point=record
       x,y:integer;
       end;
     pr=record
        a,b,c:integer;
        end;
     tr=record
        a,b,c:pr;
        end;

var a,b,c:point;
    d:tr;
    n,i,r:integer;
function makepr(a,b,c:point):pr;
begin
  result.a:=a.y-b.y;
  result.b:=b.x-a.x;
  result.c:=-result.a*a.x-result.b*a.y;
  if (result.a*c.x+result.b*c.y+result.c)<0 then
    begin
      result.a:=-result.a;
      result.b:=-result.b;
      result.c:=-result.c;
    end;
end;
function s:real;
var v1,v2:point;
begin
  v1.x:=b.x-a.x;
  v1.y:=b.y-a.y;
  v2.x:=c.x-a.x;
  v2.y:=c.y-a.y;
  result:=(v1.x*v2.y-v1.y*v2.x)/2;
  result:=abs(result);
end;

function intr(a:point):boolean;
begin
  result:=(d.a.a*a.x+d.a.b*a.y+d.a.c>=0);
  result:=result and (d.b.a*a.x+d.b.b*a.y+d.b.c>=0);
  result:=result and (d.c.a*a.x+d.c.b*a.y+d.c.c>=0);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a.x,a.y);
  read(b.x,b.y);
  read(c.x,c.y);
  d.a:=makepr(a,b,c);
  d.b:=makepr(a,c,b);
  d.c:=makepr(b,c,a);
  writeln(s:0:1);
  read(n);
  r:=0;
  for i:=1 to n do
    begin
      read(a.x,a.y);
      if intr(a) then inc(r);
    end;
  write(r);
end.