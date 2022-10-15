{$APPTYPE CONSOLE}
{$R-,Q-}

uses
  Math;

var g:array[1..1000,1..1000] of record
                            v,cs,ce:integer;
                            end;
   n,m,k,a,b,gm,t,i,a1,b1,j:integer;
   d:array[1..1000] of integer;
   used:array[1..1000] of boolean;
   mar:array[1..1000] of integer;

function time(s,x,y:integer):integer;
begin
  if (g[x,y].cs<=s) and (g[x,y].ce>=s) then s:=g[x,y].ce;
  result:=s+g[x,y].v;
end;

procedure deykstra;
var i,num,mi,j:integer;
begin
  for i:=1 to n do
    d[i]:=maxlongint div 2;
  d[a]:=0;
  for i:=1 to n-1 do
  begin
    num:=0;
    mi:=maxlongint div 2;
    for j:=1 to n do
     if not used[j] and (d[j]<mi) then
       begin
         mi:=d[j];
         num:=j;
       end;
    if num=0 then break;
    used[num]:=true;
    for j:=1 to n do
      if g[num,j].v<>0 then
        d[j]:=min(d[j],time(d[num],num,j));
  end;
  write(d[b]);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  read(a,b,k,gm);
  for i:=1 to n do
    for j:=1 to n do
      begin
      g[i,j].cs:=-1;
      g[i,j].ce:=-1;
      end;
  for i:=1 to gm do
    read(mar[i]);
  for i:=1 to m do
    begin
      read(a1,b1,t);
      g[a1,b1].v:=t;
      g[b1,a1].v:=t;
    end;
  t:=-k;
  for i:=1 to gm-1 do
    begin
      g[mar[i],mar[i+1]].cs:=t;
      g[mar[i+1],mar[i]].cs:=t;
      g[mar[i],mar[i+1]].ce:=t+g[mar[i+1],mar[i]].v;
      g[mar[i+1],mar[i]].ce:=t+g[mar[i+1],mar[i]].v;
      t:=t+g[mar[i],mar[i+1]].v;
    end;
 deykstra;
end.