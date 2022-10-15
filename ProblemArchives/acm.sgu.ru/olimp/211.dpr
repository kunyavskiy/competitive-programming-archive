{$APPTYPE CONSOLE}
{$O+}

uses
  Math;

var a,b:array[1..15000] of integer;
    m,n,i,m1,m2:integer;

procedure aqsort(l,r:integer);
var m,i,j,t:integer;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while a[i]<m do inc(i);
    while a[j]>m do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then aqsort(l,j);
  if i<r then aqsort(i,r);
end;

{procedure bqsort(l,r:integer);
var m,i,j,t:integer;
begin
  m:=b[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while b[i]<m do inc(i);
    while b[j]>m do dec(j);
    if i<=j then
    begin
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then aqsort(l,j);
  if i<r then aqsort(i,r);
end;}

function minbin (x:integer):integer;
var l,r:integer;
begin
 l:=1;
 r:=n+1;
 while r-l>1 do
  begin
   if a[(l+r) div 2]>=x then r:=(l+r) div 2
     else  l:=(l+r) div 2;
  end;
 if a[l]>x then result:=maxlongint
 else result:=x-a[l];
end;


function maxbin (x:integer):integer;
var l,r:integer;
begin
 l:=1;
 r:=n+1;
 while r-l>1 do
  begin
   if a[(l+r) div 2]>=x then r:=(l+r) div 2
     else  l:=(l+r) div 2;
  end;
 if a[l]<x then inc(l);
 result:=maxlongint;
 if l<=n then
 result:=a[l]-x;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do read(a[i]);
  for i:=1 to m do read(b[i]);
  aqsort(1,n);
  for i:=1 to m do
   begin
   m1:=maxbin(b[i]);
   m2:=minbin(b[i]);
   write(min(m1,m2),' ');
   end;
end.