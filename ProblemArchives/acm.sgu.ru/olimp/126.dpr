{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;

type line=record
           a,b,c:real;
           end;

var t:array [1..600] of record
                      x,y:integer;
                      end;
    a:array [1..180000] of line;
    k,n,i,j,m,k1:integer;
    p:line;

procedure makeline (x1,y1,x2,y2:integer);
var a1,b1,c1:int64;
begin
  a1:=y1-y2;
  b1:=x2-x1;
  c1:=x1*a1+y1*b1;
  inc(k);
  if a1<>0 then
    begin
      a[k].a:=1;
      a[k].b:=b1/a1;
      a[k].c:=c1/a1;
    end
  else
    begin
      a[k].a:=0;
      a[k].b:=1;
      a[k].c:=c1/b1;
    end;
end;

procedure swap (var a,b:line);
var t:line;
begin
 t:=a;
 a:=b;
 b:=t;
end;

function bol(var a1,b1:line):boolean;
begin
  result:=a1.a>b1.a;
  result:=result or ((a1.a=b1.a) and (a1.b>b1.b));
  result:=result or ((a1.a=b1.a) and (a1.b=b1.b) and (a1.c>b1.c));
end;

function ravn(var a1,b1:line):boolean;
begin
  result:=a1.b=b1.b;
  result:=result and (a1.c=b1.c)
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m:line;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while bol(a[i],m) do inc(i);
    while bol(m,a[j]) do dec(j);
    if i<=j then
    begin
      swap(a[i],a[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
      read(t[i].x);
      read(t[i].y);
    end;
  k:=0;
  for i:=1 to n do
   for j:=i+1 to n do
    makeline(t[i].x,t[i].y,t[j].x,t[j].y);
  qsort(1,k);
  p:=a[1];
  k1:=1;
  m:=1;
  for i:=2 to k do
   begin
    if ravn(a[i],p)then inc(k1)
    else
     begin
      p:=a[i];
      m:=max(m,k1);
      k1:=1;
     end;
   end;
  m:=max(m,k1);
  if n>1 then write((1+trunc(sqrt(1+8*m))) div 2)
  else write(1);
end.