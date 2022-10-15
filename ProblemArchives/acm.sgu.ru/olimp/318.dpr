{$APPTYPE CONSOLE}

uses
  Math;

var c:array[1..100] of int64;
    g:array[1..100,1..100] of int64;
    mi,num1,num2,k,m,i,j,a,b,n:integer;
function nedovolstvo(a,b:integer):int64;
var i:integer;
begin
  result:=0;
  for i:=1 to n do
    result:=result+c[i]*min(g[i,a],g[i,b]);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    read(c[i]);
  for i:=1 to n do
    for j:=1 to n do
      g[i,j]:=maxlongint div 2;
  for i:=1 to n do
    g[i,i]:=0;
  for i:=1 to m do
    begin
      read(a);
      read(b);
      read(g[a,b]);
      g[b,a]:=g[a,b];
    end;
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        g[i,j]:=min(g[i,j],g[i,k]+g[k,j]);
  mi:=maxlongint div 2;
  num1:=0;
  num2:=0;
  for i:=1 to n do
    for j:=1 to n do
      begin
       k:=nedovolstvo(i,j);
      if mi>k then
        begin
          mi:=k;
          num1:=i;
          num2:=j;
        end;
      end;
  writeln(mi);
  write(num1,' ',num2);
end.

