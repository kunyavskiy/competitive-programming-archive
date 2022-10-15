{$APPTYPE CONSOLE}

uses
  SysUtils;

var kol,n,i:integer;

procedure fib(a,b:integer);
begin
 inc(kol);
 if b>a then
  fib(b-a,a);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  kol:=0;
  for i:=1 to n-1 do
    fib(i,n-i);
  write(kol);
end.