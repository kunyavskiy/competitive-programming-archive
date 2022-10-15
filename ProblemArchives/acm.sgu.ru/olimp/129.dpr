{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;


var t,a:array[0..801,0..801] of integer;
    n,m,i,j:integer;
    c:char;

procedure din(var x,y:integer);
var l,maxv,sum,r,i:integer;
begin
  if a[x,y]=-maxlongint div 2 then
    begin
      t[x,y]:=-maxlongint div 2;
      inc(y);
      if y=m+1 then
        begin
          y:=1;
          inc(x);
        end;
      exit;
    end;
  l:=y;
  r:=y;
  maxv:=-maxlongint div 2;
  while (r<=m) and (a[x,r]<>-maxlongint div 2) do
    inc(r);
  sum:=0;
  for i:=l to r-1 do
    sum:=sum+a[x,i];
  for i:=l to r-1 do
     maxv:=max(maxv,t[x-1,i]);
  if maxv=-maxlongint div 2 then
     sum:=-maxlongint div 2
  else
     sum:=sum+maxv;
  for i:=l to r-1 do
     t[x,i]:=sum;
  t[x,r]:=-maxlongint div 2;
  y:=r+1;
  if y>m then
     begin
       y:=1;
       inc(x);
     end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=0 to n+1 do
    begin
      t[i,0]:=-maxlongint div 2;
      t[i,m+1]:=-maxlongint div 2;
    end;
  for i:=0 to m+1 do
    begin
      t[0,i]:=-maxlongint div 2;
      t[n+1,i]:=-maxlongint div 2;
    end;
  t[0,1]:=0;
  for i:=1 to n do
   begin
    for j:=1 to m do
      begin
        read(c);
        if c='*' then
          a[i,j]:=-maxlongint div 2
        else
          a[i,j]:=ord(c)-ord('0');
      end;
    readln;
    end;

  i:=1;
  j:=1;
  while i<=n do
      din(i,j);
  if t[n,m]=-maxlongint div 2  then
    write('SEE YOU LATER')
  else
    write(t[n,m]);


end.