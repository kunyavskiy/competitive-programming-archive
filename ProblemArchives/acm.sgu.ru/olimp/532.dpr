{$APPTYPE CONSOLE}

uses
  SysUtils;

var a:array[1..100] of integer;
    n,i,b,k:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
   read(a[i]);
  read(k);
  for i:=1 to k do
    begin
      read(b);
      dec(a[b]);
    end;
  for i:=1 to n do
    if a[i]<0 then writeln('yes')
    else writeln('no');

end.