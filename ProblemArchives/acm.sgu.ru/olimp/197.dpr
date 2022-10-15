{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;

var a:array[0..15000] of int64;
    t,n,m:int64;
    i:integer;
    res,resmin:int64;
function dest(a,b:integer):int64;
begin
  result:=((a-b)+(n+1)) mod (n+1);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(m,n);
  for i:=1 to n do
   begin
    read(t);
    inc(a[t]);
   end;
  res:=0;
  for i:=0 to n do
    res:=res+dest(0,i)*a[i];
  resmin:=res;
  for i:=1 to n do
    begin
      res:=res+m;
      res:=res-a[i]*(n+1);
      resmin:=min(resmin,res);
    end;
  write(resmin);
end.