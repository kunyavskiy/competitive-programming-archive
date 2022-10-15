{$APPTYPE CONSOLE}

uses Math;

type point=record
       x,y:real;
       end;

var n,s1num,h,s2num,i:integer;
    a:array[1..32] of point;
    b:array[1..32] of point;
    ugol:array[1..32] of real;
    s1,s2:point;
    p,p1:real;

function ravn(a,b:point):boolean;
begin
  result:=(abs(a.x-b.x)<0.001) and (abs(a.y-b.y)<0.001);
end;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

function dest(a,b:point):real;
var  dx,dy:real;
begin
  dx:=a.x-b.x;
  dy:=a.y-b.y;
  result:=sqrt(dx*dx+dy*dy);
end;

function  perim(l,r:integer):real;
var i:integer;
begin
  result:=0;
  for i:=l+1 to r do
    result:=result+dest(b[i],b[i-1]);

end;


procedure makenugol;
var u,du,r:real;
    i:integer;
    o:point;
begin
  u:=arctan2(a[1].y,a[1].x);
  if u<0 then u:=u+2*pi;
  du:=2*pi/n;
  o.x:=0;
  o.y:=0;
  r:=dest(o,a[1]);
  for i:=2 to n do
    begin
      u:=u+du;
      a[i].x:=r*cos(u);
      a[i].y:=r*sin(u);
    end;
end;
procedure swappoint(var a,b:point);
var t:point;
begin
  t:=a;
  a:=b;
  b:=t;
end;
procedure swapreal(var a,b:real);
var t:real;
begin
  t:=a;
  a:=b;
  b:=t;
end;
procedure qsort(l,r:integer);
var i,j: integer;
    m:real;
begin
  m :=ugol[random(r-l+1)+l];
  i:=l;
  j:=r;
  repeat
    while ugol[i]<m do inc(i);
    while ugol[j]>m do dec(j);
    if i<=j then
    begin
      swapreal(ugol[i],ugol[j]);
      swappoint(a[i],a[j]);
      inc(i); dec(j);
    end;
  until i > j;

  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;


function sbol0 (a,b,c:point):boolean;
var s:real;
begin
  s:=a.x*b.y-a.y*b.x;
  s:=s+b.x*c.y-b.y*c.x;
  s:=s+c.x*a.y-c.y*a.x;
  result:=s>=0;
end;


procedure push(x:point);
begin
  inc(h);
  b[h]:=x;
end;
procedure pop;
begin
  dec(h);
end;
procedure vipobol;
var num,i:integer;
    c:point;
begin
  num:=1;
  for i:=2 to n+2 do
    if (a[i].y<a[num].y) or ((a[i].y=a[num].y) and (a[i].x<a[i].x)) then
    num:=i;
  c:=a[num];
  for i:=1 to num-1 do
    begin
      a[i].x:=a[i].x-a[num].x;
      a[i].y:=a[i].y-a[num].y;
      ugol[i]:=arctan2(a[i].y,a[i].x);
    end;
  for i:=num+1 to n+2 do
    begin
      a[i].x:=a[i].x-a[num].x;
      a[i].y:=a[i].y-a[num].y;
      ugol[i]:=arctan2(a[i].y,a[i].x);
    end;
  a[num].x:=0;
  a[num].y:=0;
  ugol[num]:=0;
  swapreal(ugol[num],ugol[1]);
  swappoint(a[num],a[1]);
  qsort(2,n+2);
  for i:=1 to n+2 do
     begin
       a[i].x:=a[i].x+c.x;
       a[i].y:=a[i].y+c.y;
       while (h>=2) and (not sbol0(b[h-1],b[h],a[i])) do pop;
       push(a[i]);
     end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  read(a[1].x);
  read(a[1].y);
  makenugol;
  read(a[n+1].x);
  read(a[n+1].y);
  read(a[n+2].x);
  read(a[n+2].y);
  s1:=a[n+1];
  s2:=a[n+2];
  vipobol;
  p:=perim(1,h)+dest(b[1],b[h]);
  s1num:=0;
  s2num:=0;
  for i:=1 to h do
    begin
      if ravn(b[i],s1) then s1num:=i;
      if ravn(b[i],s2) then s2num:=i;
    end;
  if s1num>s2num then swap(s1num,s2num);
  if s1num=0 then
    begin
    write(dest(s1,s2):0:2);
    close(input);
    close(output);
    halt;
    end;
  p1:=perim(s1num,s2num);
  write(min(p1,p-p1):0:2);
end.