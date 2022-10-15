{$APPTYPE CONSOLE}

var  a,b,c:array[1..1000] of integer;
     h,s,k,i,j,l,res:integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsorta(l,r:integer);
var i,j,m:integer;
begin
  i:=l;
  j:=r;
  m:=a[random(r-l+1)+l];
  while i<j do
    begin
      while a[i]<m do inc(i);
      while a[j]>m do dec(j);
      if i<=j then
        begin
          swap(a[i],a[j]);
          inc(i);
          dec(j);
        end;
    end;
 if l<j then qsorta(l,j);
 if i<r then qsorta(i,r);
end;

procedure qsortb(l,r:integer);
var i,j,m:integer;
begin
  i:=l;
  j:=r;
  m:=b[random(r-l+1)+l];
  while i<j do
    begin
      while b[i]<m do inc(i);
      while b[j]>m do dec(j);
      if i<=j then
        begin
          swap(b[i],b[j]);
          inc(i);
          dec(j);
        end;
    end;
 if l<j then qsortb(l,j);
 if i<r then qsortb(i,r);
end;

procedure qsortc(l,r:integer);
var i,j,m:integer;
begin
  i:=l;
  j:=r;
  m:=c[random(r-l+1)+l];
  while i<j do
    begin
      while c[i]<m do inc(i);
      while c[j]>m do dec(j);
      if i<=j then
        begin
          swap(c[i],c[j]);
          inc(i);
          dec(j);
        end;
    end;
 if l<j then qsortc(l,j);
 if i<r then qsortc(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(h,s,k);
  for i:=1 to h do
    read(a[i]);
  qsorta(1,h);
  for i:=1 to s do
    read(b[i]);
  qsortb(1,s);
  for i:=1 to k do
    read(c[i]);
  qsortc(1,k);
  i:=1;
  j:=1;
  l:=1;
  while (i<=h) and (j<=s) and (l<=k) do
    begin
      while b[j]<=a[i] do inc(j);
      while c[l]<=b[j] do inc(l);
      if (i<=h) and (j<=s) and (l<=k) then
        begin
         inc(res);
         inc(i);
         inc(j);
         inc(l);
        end;
    end;
  write(res);
end.
