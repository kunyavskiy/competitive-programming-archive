{$APPTYPE CONSOLE}

uses
  Math;

var n,i,j:integer;
    a:array[1..100] of string;
    q:boolean;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do
    readln(a[i]);
  for i:=1 to length(a[1]) do
  begin
    q:=true;
    for j:=1 to n do
      if a[j][i]<>a[1][i] then
         q:=false;
    if not q then
       write('?')
    else
       write(a[1][i]);
  end;



end.