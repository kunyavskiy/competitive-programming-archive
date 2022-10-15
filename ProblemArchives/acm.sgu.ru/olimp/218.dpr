{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;
var g:array[1..100,1..100] of integer;
    n,m,i,j,a,b,c,d,cik:integer;
    used:array[1..100] of boolean;

function fb(s:integer):integer;
var d:array[1..100,0..100] of integer;
    i,j,k:integer;
begin
 if used[s] then
   begin
     result:=n+1;
     exit;
   end;
 used[s]:=true;
  for i:=1 to n do
    for j:=0 to cik-1 do
      d[i,j]:=maxlongint div 2;
  d[s,0]:=0;
  for k:=1 to cik-1 do
  begin
    for i:=1 to n do
      for j:=1 to n do
        if  g[i,j]<>maxlongint div 2 then
           d[j,k]:=min(min(d[j,k-1],d[j,k]),d[i,k-1]+g[i,j]);
    if d[s,k]<0 then
      begin
       result:=k;
       exit;
      end;
  end;
  result:=n+1;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  randomize;
  read(n,m);
  for i:=1 to n do
    for j:=1 to n do
        g[i,j]:=maxlongint div 2;
  for i:=1 to m do
    begin
      read(a,b,c,d);
      g[a,b]:=-c;
      g[b,a]:=-d;
    end;
  cik:=n+1;
  for i:=1 to 10000 do
    cik:=min(cik,fb(random(n)+1));
  if cik=n+1 then write(0)
  else write(cik);

end.