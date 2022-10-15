{$APPTYPE CONSOLE}

var a:array[1..15000] of integer;
    n,i,d,l,r,res:integer;


procedure qsort(l,r:integer);
var m,i,j,t:integer;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while a[i]<m do inc(i);
    while a[j]>m do dec(j);
    if i <= j then
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
  read(n,d);
  for i:=1 to n do
    read(a[i]);
  qsort(1,n);
  l:=1;
  r:=n;
  res:=0;
  while l<r do
    begin
      while (l<r) and (a[l]+a[r]>d) do
        begin
          inc(res);
          dec(r);
        end;
      inc(res);
      inc(l);
      dec(r);
    end;
  if l=r then inc(res);
  write(res);
end.