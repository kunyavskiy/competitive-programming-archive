{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

var t,a:array[0..801,0..801] of integer;
    n,m,i,j:integer;
    c:char;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do
   for j:=1 to m do
   begin
     read(c);
     if j=m then readln;
     if c='*' then a[i,j]:=10
     else a[i,j]:=strtoint(c);
   end;
   fillchar(t,sizeof(t),-1);
   t[1,1]:=0;
  for i:=1 to n do
    for j:=1 to m do
     if (a[i,j]<10) and (t[i,j]>-1) then
     begin
     t[i+1,j]:=max(t[i,j]+a[i+1,j],t[i+1,j]);
     t[i,j+1]:=max(t[i,j]+a[i,j+1],t[i,j+1]);
     end;
  if t[n,m]=-1 then write('SEE YOU LATER')
  else write(t[n,m])
end.