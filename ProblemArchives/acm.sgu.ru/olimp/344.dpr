{$APPTYPE CONSOLE}

uses
  Math;
var i,j,k,l,n,m:integer;
    a:array[1..10,1..10] of integer;
    ma,mi:real;

function sred(x1,y1,x2,y2:integer):real;
var i,j:integer;
begin
  result:=0;
  for i:=x1 to x2 do
     for j:=y1 to y2 do
       result:=result+a[i,j];
  result:=result/(x2-x1+1)/(y2-y1+1)
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    for j:=1 to m do
    read(a[i,j]);
  ma:=-(maxlongint div 2);
  for i:=1 to n do
    for j:=1 to m do
      begin
      mi:=maxlongint div 2;
      for k:=0 to i-1 do
        for l:=0 to j-1 do
          mi:=min(mi,sred(i-k,j-l,i,j));
      ma:=max(ma,mi);
      end;
  write(ma:0:4);
end.