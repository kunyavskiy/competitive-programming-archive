{$APPTYPE CONSOLE}

uses
  Math;

type point=record
        x,y:integer;
        end;
     pr=record
        a,b:point;
        end;

var pr1,pr2:pr;

function s(p:pr):integer;
var sx,sy:integer;
begin
  sx:=p.b.x-p.a.x;
  sy:=p.a.y-p.b.y;
  result:=sx*sy;
end;

function sper:integer;
var per:pr;
begin
  per.a.y:=min(pr1.a.y,pr2.a.y);
  per.b.y:=max(pr1.b.y,pr2.b.y);
  per.a.x:=max(pr1.a.x,pr2.a.x);
  per.b.x:=min(pr1.b.x,pr2.b.x);
  if (per.a.y-per.b.y<=0) or((per.b.x-per.a.x)<0) then result:=0 else
  result:=s(per);
end;

function norm(p:pr):pr;
begin
  result.a.x:=min(p.a.x,p.b.x);
  result.b.x:=max(p.a.x,p.b.x);
  result.b.y:=min(p.a.y,p.b.y);
  result.a.y:=max(p.a.y,p.b.y);
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(pr1.a.x,pr1.a.y);
  read(pr1.b.x,pr1.b.y);
  read(pr2.a.x,pr2.a.y);
  read(pr2.b.x,pr2.b.y);
  pr1:=norm(pr1);
  pr2:=norm(pr2);
  write(s(pr1)+s(pr2)-sper);
end.