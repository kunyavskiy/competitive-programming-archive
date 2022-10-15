{$APPTYPE CONSOLE}
uses
  math;
var f:array[0..20] of int64;
    i,n:integer;
    r:int64;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  f[0]:=1;
  read(n);
  for i:=1 to n do
    f[i]:=f[i-1]*i;
  r:=0;
  for i:=3 to n do
     r:=r+trunc(f[n]/f[n-i]/2/i);
  write(r);
end.

