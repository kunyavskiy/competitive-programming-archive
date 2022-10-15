{$APPTYPE CONSOLE}

uses
  SysUtils;

var a,i,b,n,m,kom:integer;
    color:array[1..100] of integer;
    g:array[1..100,1..100] of boolean;
procedure write2power(b:integer);
var a:array[1..50] of integer;
    l,i,c,x:integer;
begin
  fillchar(a,sizeof(a),0);
  a[1]:=1;
  for l:=1 to b do
    begin
      c:=0;
      for i:=1 to 50 do
       begin
         c:=c+a[i]*2;
         a[i]:=c mod 10;
         c:=c div 10;
       end;
    end;
  x:=50;
  while a[x]=0 do dec(x);
  for i:=x downto 1 do
    write(a[i]);
end;

procedure dfs(v,c:integer);
var i:integer;
begin
  if color[v]=c then exit;
  if color[v]<>-1 then
    begin
      write(0);
      close(input);
      close(output);
      halt;
    end;
  color[v]:=c;
  for i:=1 to n do
    if g[v,i] then dfs(i,1-c);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  fillchar(color,sizeof(color),-1);
  for i:=1 to m do
    begin
      read(a,b);
      g[a,b]:=true;
      g[b,a]:=true;
    end;
  kom:=0;
  for i:=1 to n do
    if color[i]=-1 then
      begin
        inc(kom);
        dfs(i,1);
      end;
  write2power(kom);
end.