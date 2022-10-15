{$APPTYPE CONSOLE}

uses
   Math;

var t,from:array[0..100,1..2] of integer;
    a:array[0..100] of integer;
    n,i,m,num,temp:integer;
procedure nvp;
var i,j:integer;
begin
  for i:=1 to n do
    begin
      t[i,1]:=1;
      from[i,1]:=0;
      for j:=1 to i do
        if (a[j]<a[i]) and (t[j,1]+1>t[i,1]) then
           begin
             t[i,1]:=t[j,1]+1;
             from[i,1]:=j;
           end;
    end;
end;

procedure ndp;
var i,j:integer;
begin
    for i:=n downto 1 do
    begin
      t[i,2]:=1;
      from[i,2]:=0;
      for j:=i+1 to n do
        if (a[j]<a[i]) and (t[j,2]+1>t[i,2]) then
           begin
             t[i,2]:=t[j,2]+1;
             from[i,2]:=j;
           end;
    end;
end;

procedure printdown(a,kol:integer);
begin
  if kol=0 then exit;
  printdown(from[a,1],kol-1);
  write(a,' ')
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(a[i]);
  nvp;
  ndp;
  m:=0;
  num:=0;
  for i:=1 to n do
    if min(t[i,1],t[i,2])>m then
       begin
         m:=min(t[i,1],t[i,2]);
         num:=i;
       end;
  writeln(m-1);
  printdown(num,m);
  temp:=num;
  for i:=1 to m-1 do
    begin
      temp:=from[temp,2];
      write(temp,' ');
    end;
end.