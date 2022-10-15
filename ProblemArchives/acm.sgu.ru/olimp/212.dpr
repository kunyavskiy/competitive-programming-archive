{$APPTYPE CONSOLE}
{$H+,r-,q-,o-}


type coord=record
     x,y,h:integer;
     end;
var a:array[1..2001] of coord;
    n,xt,m,yt,i:integer;
    c1,c2:char;

function Min(const A, B: Integer): Integer;
begin
  if A < B then
    Result := A
  else
    Result := B;
end;


function bol(a,b:coord):boolean;
begin
  result:=a.x>=b.x;
  if not result then exit;
  result:=a.x>b.x;
  if result then exit;
  result:=a.y>=b.y;
  if not result then exit;
  result:=a.y>b.y;
  if result then exit;
  result:=a.h>=b.h;
  if not result then exit;
  result:=a.h>b.h;
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m,t:coord;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while bol(m,a[i])do inc(i);
    while bol(a[j],m) do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  xt:=0;
  yt:=0;
  a[1].x:=0;
  a[1].y:=0;
  a[1].h:=0;
  for i:=1 to n do
   begin
     read(c1);
     while c1=' ' do read(c1);
     read(c2);
     if (c1='R') then inc(yt);
     if (c1='L') then dec(yt);
     if (c1='U') or (c2='U') then dec(xt);
     if (c1='D') or (c2='D') then inc(xt);
     a[i+1].x:=xt;
     a[i+1].y:=yt;
     a[i+1].h:=i;
   end;
   qsort(1,n+1);
   m:=100000000;
   for i:=2 to n do
     if (a[i].x=a[i-1].x) and (a[i].y=a[i-1].y) then
       m:=min(m,a[i].h);
   if m=100000000 then write('NO')
   else
     begin
       writeln('YES');
       write(m);
     end;
end.