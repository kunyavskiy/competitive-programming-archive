{$APPTYPE CONSOLE}

uses
  Math;

type point=record
       x,y:int64;
       end;

var points:array[1..1500] of point;
    dest:array[1..1500] of int64;
    n,i,j,last:integer;
    res,onepriam:int64;

function destsqr(a,b:point):int64;
begin
  result:=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
end;

function kolpar(x:int64):int64;
begin
  result:=trunc(x*(x-1)/2)
end;

procedure swap(var a,b:int64);
var t:int64;
begin
  t:=a;
  a:=b;
  b:=t;
end;

function less(a,b:point):boolean;
begin
  result:=a.x<b.x;
  result:=result or ((a.x=b.x) and (a.y<b.y));
end;


procedure qsortpoint(l,r:integer);
var i,j:integer;
    m:point;
begin
  m:=points[random(r-l+1)+l];
  i:=l;
  j:=r;
  while i<=j do
    begin
       while less(points[i],m) do inc(i);
       while less(m,points[j]) do dec(j);
       if i<=j then
         begin
           swap(points[i].x,points[j].x);
           swap(points[i].y,points[j].y);
           inc(i);
           dec(j);
         end;
    end;
  if l<j then qsortpoint(l,j);
  if i<r then qsortpoint(i,r);

end;

function makepoint(a,b:int64):point;
begin
  result.x:=a;
  result.y:=b;
end;

procedure qsortdest(l,r:integer);
var i,j:integer;
    m:int64;
begin
  m:=dest[random(r-l+1)+l];
  i:=l;
  j:=r;
  while i<=j do
    begin
       while dest[i]<m do inc(i);
       while dest[j]>m do dec(j);
       if i<=j then
         begin
           swap(dest[i],dest[j]);
           inc(i);
           dec(j);
         end;
    end;
  if l<j then qsortdest(l,j);
  if i<r then qsortdest(i,r);

end;


function bin(x:point):boolean;
var l,r,m:integer;
begin
  l:=1;
  r:=n+1;
  while l<r-1 do
    begin
      m:=(l+r) div 2;
      if (points[m].x=x.x)  and (points[m].y=x.y) then
        begin
          result:=true;
          exit;
        end;
      if less(x,points[m]) then
        r:=m
      else l:=m;
    end;
  result:=(points[l].x=x.x)  and (points[l].y=x.y);
end;
begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(n);
   for i:=1 to n do
     read(points[i].x,points[i].y);
   res:=0;
   for i:=1 to n do
     begin
       for j:=1 to n do
         dest[j]:=destsqr(points[i],points[j]);
       qsortdest(1,n);
       last:=1;
       for j:=2 to n do
         if dest[j]<>dest[last] then
           begin
             res:=res+kolpar(j-last);
             last:=j;
           end;
       res:=res+kolpar(n-last+1);
     end;
  qsortpoint(1,n);
  onepriam:=0;
  for i:=1 to n do
    for j:=1 to n do
      if (i<>j) and (bin(makepoint(2*points[j].x-points[i].x,2*points[j].y-points[i].y))) then
        inc(onepriam);
  res:=res-(onepriam div 2);
  write(res);
end.