{$APPTYPE CONSOLE}
{$R+,Q+}

uses
   Math;

var a:array[0..60] of int64;
    stack:array[0..60] of int64;
    b:array[0..60] of int64;
    h,m,n,i:integer;
    p:int64;
procedure push(x:int64);
begin
  inc(h);
  stack[h]:=x;
end;

function pop:integer;
begin
   result:=stack[h];
   dec(h);
end;

procedure soeden(l:integer);
var i:integer;
begin
   p:=p+a[l]+a[l-1];
   push(b[l-1]);
   a[l-1]:=a[l]+a[l-1];
   b[l-1]:=b[l];
  for i:=l to m-1 do
    begin
      a[i]:=a[i+1];
      b[i]:=b[i+1];
    end;
  dec(m);
end;

function findminsum:integer;
var mi,i:integer;
begin
  mi:=maxlongint div 2;
  result:=1;
  for i:=2 to m do
    if mi>a[i]+a[i-1] then
      begin
        result:=i;
        mi:=a[i]+a[i-1];
      end;
end;

procedure qsort(l,r:integer);
var m,i,j,t:integer;
begin
  m:=b[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while b[i] < m do inc(i);
    while b[j] > m do dec(j);
    if i<=j then
    begin
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to m do read(b[i]);
  qsort(1,m);
  inc(m);
  b[m]:=n;
  a[1]:=b[1];
  for i:=2 to m do
    a[i]:=b[i]-b[i-1];
  p:=0;
  h:=0;
  while m>1 do
    soeden(findminsum);
  writeln(p);
  while h>0 do
    write(pop,' ')

end.