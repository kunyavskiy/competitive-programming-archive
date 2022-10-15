{$apptype console}

uses
  Math;

type abcd=record
         num:integer;
         znach:real;
         end;

var a:array[1..100000] of abcd;
    res:array[1..100000] of integer;
    n,nc,i,minnum:integer;
    up,down,mi:real;

procedure swap(var a,b:abcd);
var t:abcd;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m:real;
begin
  i:=random(r-l+1)+l;
  m:=a[i].znach-trunc(a[i].znach);
  i:=l;
  j:=r;
  while i<=j do
    begin
      while a[i].znach-trunc(a[i].znach)>m do inc(i);
      while a[j].znach-trunc(a[j].znach)<m do dec(j);
      if i<=j then
        begin
          swap(a[i],a[j]);
          inc(i);
          dec(j);
        end;
    end;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r); 

end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  nc:=n;
  for i:=1 to n do
    begin
      read(a[i].znach);
      a[i].num:=i;
    end;
  i:=1;
  while i<=n do
   begin
    if a[i].znach=trunc(a[i].znach) then
      begin
        swap(a[i],a[n]);
        dec(n);
      end;
    inc(i);
   end;
  qsort(1,n);
  down:=0;
  up:=0;
  for i:=1 to n do
     down:=down+a[i].znach-trunc(a[i].znach);
  mi:=down;
  minnum:=0;
  for i:=1 to n do
    begin
       down:=down-a[i].znach+trunc(a[i].znach);
       up:=up+1-(a[i].znach-trunc(a[i].znach));
       if mi>max(up,down) then
         begin
           minnum:=i;
           mi:=max(up,down);
         end;
    end;
  for i:=1 to nc do
    if i<=minnum then
      res[a[i].num]:=trunc(a[i].znach)+1
    else
       res[a[i].num]:=trunc(a[i].znach);
  for i:=1 to nc do
    write(res[i],' ');



end.