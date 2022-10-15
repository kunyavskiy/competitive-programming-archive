{$APPTYPE CONSOLE}
uses
  SysUtils,math;
type v =record
        x:integer;
        y:integer;
        l:real
        end;
    int=integer;
var v1,v2,v3,v4:array[1..50] of v;
    n,v1c,v2c,v3c,v4c,x1,y1,i:int;
    vs:array[1..4] of v;
    m:real;
function len (x,y:int):real;
begin
len:=sqrt(sqr(x)+sqr(y));
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
v1c:=0;
v2c:=0;
v3c:=0;
v4c:=0;
read(n);
for i:=1 to n do
begin
  read(x1);
  read(y1);
  if ((x1>=0) and (y1>=0))then
  begin
    inc(v1c);
    v1[v1c].x:=x1;
    v1[v1c].y:=y1;
  end
  else  if ((x1<=0) and (y1>=0))then
  begin
    inc(v2c);
    v2[v2c].x:=x1;
    v2[v2c].y:=y1;
  end
  else  if ((x1<=0) and (y1<=0))then
    begin
      inc(v3c);
      v3[v3c].x:=x1;
      v3[v3c].y:=y1;
    end
    else  if ((x1>=0) and (y1<=0))then
    begin
    inc(v4c);
    v4[v4c].x:=x1;
    v4[v4c].y:=y1;
    end;
end;
for i:=1 to v1c do
begin
vs[1].x:=vs[1].x+v1[i].x;
vs[1].y:=vs[1].y+v1[i].y;
end;
for i:=1 to v2c do
begin
vs[2].x:=vs[2].x+v2[i].x;
vs[2].y:=vs[2].y+v2[i].y;
end;
for i:=1 to v3c do
begin
vs[3].x:=vs[3].x+v3[i].x;
vs[3].y:=vs[3].y+v3[i].y;
end;
for i:=1 to v4c do
begin
vs[4].x:=vs[4].x+v4[i].x;
vs[4].y:=vs[4].y+v4[i].y;
end;
vs[1].l:=len(vs[1].x,vs[1].y);
vs[2].l:=len(vs[2].x,vs[2].y);
vs[3].l:=len(vs[3].x,vs[3].y);
vs[4].l:=len(vs[4].x,vs[4].y);
for i:=1 to v2c do vs[1].l:=max(vs[1].l,len(vs[1].x+v2[i].x,vs[1].y+v2[i].y));
for i:=1 to v4c do vs[1].l:=max(vs[1].l,len(vs[1].x+v4[i].x,vs[1].y+v4[i].y));
for i:=3 to v2c do vs[3].l:=max(vs[3].l,len(vs[3].x+v2[i].x,vs[3].y+v2[i].y));
for i:=3 to v4c do vs[3].l:=max(vs[3].l,len(vs[3].x+v4[i].x,vs[3].y+v4[i].y));
for i:=2 to v1c do vs[2].l:=max(vs[2].l,len(vs[2].x+v1[i].x,vs[2].y+v1[i].y));
for i:=2 to v3c do vs[2].l:=max(vs[2].l,len(vs[2].x+v3[i].x,vs[2].y+v3[i].y));
for i:=4 to v1c do vs[4].l:=max(vs[4].l,len(vs[4].x+v1[i].x,vs[4].y+v1[i].y));
for i:=4 to v3c do vs[4].l:=max(vs[4].l,len(vs[4].x+v3[i].x,vs[4].y+v3[i].y));
m:=max(max(vs[1].l,vs[2].l),max(vs[3].l,vs[4].l));
write(m:0:11);
end.