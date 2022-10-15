{$APPTYPE CONSOLE}

uses
  SysUtils;
var n,i:integer;
    a:array[1..700000] of integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  if n=1 then
   begin
    write(1);
    close(input);
    close(output);
    halt;
   end;
  a[1]:=1;
  a[2]:=2;
  for i:=3 to n do
    begin
     a[i]:=i;
     swap(a[i],a[(i+1) div 2]);
    end;
  for i:=1 to n do
    write(a[i],' ');
end.