{$APPTYPE CONSOLE}

uses
  Math;

var a:array[1..20,1..20,1..7] of real;
    t:array[1..20,1..20,0..7] of real;
    n,m,i,j,l,k:integer;
    res:real;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  fillchar(t,sizeof(t),0);
  for i:=1 to n do
    read(t[i,i,0]);
  for i:=1 to m do
    for j:=1 to n do
      for l:=1 to n do
        read(a[j,l,i]);
 for i:=1 to m do
   for j:=1 to n do
     for l:=1 to n do
       for k:=1 to n do
         t[j,l,i]:=max(t[j,l,i],t[j,k,i-1]*a[k,l,i]);
 res:=0;
 for i:=1 to n do
    res:=res+t[i,1,m];
 write(res:0:12);
end.
