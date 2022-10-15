{$APPTYPE CONSOLE}

uses
  SysUtils;

var color:array[1..100000] of byte;
    g:array[1..100000] of array of integer;
    n,i,j:integer;
procedure kras(a,b:integer);
var i:integer;
begin
  color[a]:=b;
  for i:=1 to g[a,0] do
     kras(g[a,i],b);
end;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;


function dfs(v:integer):boolean;
var i,j:integer;
begin
  if (g[v,0] and 1=0) and (g[v,0]<>0) then
    begin
      for i:=1 to g[v,0] shr 1 do
        kras(g[v,i],0);
      for i:=(g[v,0] shr 1)+1 to g[v,0] do
        kras(g[v,i],1);
      dfs:=true;
      exit;
    end;
  result:=false;
  for i:=1 to g[v,0] do
    begin
      result:=dfs(g[v,i]);
      if result=true then
        begin
           swap(g[v,i],g[v,g[v,0]]);
           dec(g[v,0]);
           for j:=1 to g[v,0] shr 1 do
             kras(g[v,j],0);
           for j:=(g[v,0] shr 1)+1 to g[v,0] do
             kras(g[v,j],1);
           dfs:=true;
           inc(g[v,0]);
           exit;
        end;
    end;
end;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 read(n);
 for i:=1 to n do
   begin
     setlength(g[i],1);
     read(g[i,0]);
     setlength(g[i],g[i,0]+1);
     for j:=1 to g[i,0] do
       read(g[i,j]);
   end;
  fillchar(color,sizeof(color),-1);
  if dfs(1) then
     for i:=1 to n do
       if g[i,0]=0 then write(color[i])
       else
  else
  write('No solution');
end.