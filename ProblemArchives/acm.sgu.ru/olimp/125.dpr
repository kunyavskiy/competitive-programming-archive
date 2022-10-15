{$APPTYPE CONSOLE}
{$r+,q+,o-}

uses sysutils;

var n,a,k,res,i:integer;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  read(k);
  read(a);
  res:=n*a;
  for i:=1 to k-1 do
    read(a);
  write((res div a)*a);
end.