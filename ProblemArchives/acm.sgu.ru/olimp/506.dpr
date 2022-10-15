{$APPTYPE CONSOLE}
{$R+,Q+}

uses
  SysUtils, Math;



var a:array[1..50] of integer;
   n,i:integer;
   sum:int64;

procedure qsort(l, r : integer);
var m, i, j, t : integer;
begin
  m:=a[random(r-l+1)+l];
  i:=l;
  j:=r;
  repeat
    while a[i]>m do inc(i);
    while a[j]<m do dec(j);
    if i <= j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      inc(i); dec(j);
    end;
  until i > j;

  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  sum:=0;
  for i:=1 to n do begin read(a[i]); sum:=sum+a[i]; end;
  qsort(1,n);
  i:=1;
  while (a[i]>=sum-a[i]) and (i<n) do
  begin
  sum:=sum-a[i];
  inc(i);
  end;
  if i<=n-2 then write(i-1)
  else write(-1)
end.