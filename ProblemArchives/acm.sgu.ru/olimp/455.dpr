{$APPTYPE CONSOLE}

uses
  SysUtils;

type sportsmen= record
      r:integer;
      p:integer;
      s:integer;
      t:int64;
      end;

var comp:array[1..1000] of sportsmen;
    h,a,b:array[1..1000] of integer;
    n,k,i,j:integer;

procedure qsort(l,r:integer);
var i,j,mp:integer;
    m:int64;
    t:sportsmen;
begin
  i:=random(r-l+1)+l;
  m:=comp[i].t;
  mp:=comp[i].p;
  i:=l; j:=r;
  repeat
    while (comp[i].t>m) or ((comp[i].t=m) and (comp[i].p>mp)) do inc(i);
    while (comp[j].t<m) or ((comp[j].t=m) and (comp[j].p<mp)) do dec(j);
    if i<=j then
    begin
      t:=comp[i]; comp[i]:=comp[j]; comp[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

procedure hqsort(l,r:integer);
var m,i,j,t:integer;
begin
  m:=h[random(r-l+1)+l];
  i:=l;
  j:=r;
  repeat
  while h[i]>m do inc(i);
  while h[j]<m do dec(j);
  if i<=j then
    begin
    t:=h[i];
    h[i]:=h[j];
    h[j]:=t;
    inc(i);
    dec(j);
    end;
  until i>j;
  if j>l then hqsort(l,j);
  if i<r then hqsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  read(k);
  for i:=1 to n do
  begin
    read(comp[i].t);
    read(comp[i].r);
    read(comp[i].p);
    comp[i].s:=i;
  end;
  for i:=1 to k do
   read(a[i]);
  for i:=1 to n do
   read(b[i]);
  qsort(1,n);
  for i:=1 to k do
   begin
     for j:=1 to n do
      h[j]:=3*sqr(a[i])+5*a[i]*b[j]+2*sqr(b[j]);
     hqsort(1,n);
     for j:=1 to n do
       comp[j].t:=comp[j].t+h[j]+comp[j].r;
     qsort(1,n);
   end;
  for i:=1 to n do
   write(comp[i].s,' ')
end.