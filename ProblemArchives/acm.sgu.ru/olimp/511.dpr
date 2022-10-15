{$APPTYPE CONSOLE}
{$R+,Q+}

uses math;

var a:array[1..1000] of integer;
    m,n,i:integer;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(a[i]);
  m:=maxintvalue(a);
for i:=1 to n do
  write(m-a[i],' ');
end.