{$APPTYPE CONSOLE}

uses
  Math;

var color:array[1..1000] of integer;
    q:boolean;
    g:array[1..1000,1..1000] of integer;
    n,i,j,maxreb:integer;

procedure dfs(v,k,c:integer);
var i:integer;
begin
  if color[v]<>0 then
    begin
       if color[v]<>c then
         q:=false;
       exit;
    end;
  color[v]:=c;
  for i:=1 to n do
    if g[v,i]>k then
      begin
        dfs(i,k,3-c);
        if not q then exit;
      end;
end;


function bin(r:integer):integer;
var l,m,i:integer;
begin
  l:=-1;
  while r-l>1 do
    begin
      m:=(r+l) div 2;
      fillchar(color,sizeof(color),0);
      q:=true;
      for i:=1 to n do
        if q and (color[i]=0) then
          dfs(i,m,1);
      if not q then
         l:=m
      else
         r:=m;
    end;
  result:=r;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  maxreb:=0;
  for i:=1 to n-1 do
  begin
    g[i,i]:=0;
    for j:=i+1 to n do
      begin
        read(g[i,j]);
        g[j,i]:=g[i,j];
        maxreb:=max(maxreb,g[i,j]);
      end;
  end;
  write(bin(maxreb));
end.