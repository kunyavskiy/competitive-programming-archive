{$APPTYPE CONSOLE}

uses
  SysUtils;

type zar=record
        x,y,r:int64;
        end;

var n,i,j,kol:integer;
    por:array[1..200] of zar;
    g:array[1..200,1..200] of boolean;
    used,noin:array[1..200] of boolean;

function sqrdest(i,j:integer):int64;
var x1,x2,y1,y2:int64;
begin
   x1:=por[i].x;
   x2:=por[j].x;
   y1:=por[i].y;
   y2:=por[j].y;
   result:=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
end;

procedure dfs(v:integer);
var i:integer;
begin
  noin[v]:=true;
  used[v]:=true;
  for i:=1 to n do
    if g[v,i] and not used[i] then
      dfs(i);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(por[i].x,por[i].y,por[i].r);
  for i:=1 to n do
    for j:=1 to n do
        if sqrdest(i,j)<=por[i].r*por[i].r then
            g[i,j]:=true;
  for i:=1 to n do
    if not noin[i] then
      begin
        fillchar(used,sizeof(used),false);
        dfs(i);
        noin[i]:=false;
      end;
  for i:=1 to n do
    if not noin[i] then inc(kol);
  writeln(kol);
  for i:=1 to n do
    if not noin[i] then
       write(i,' ');

end.
