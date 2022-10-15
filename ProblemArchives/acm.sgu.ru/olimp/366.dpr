{$APPTYPE CONSOLE}

var g:array[1..100,1..100] of boolean;
    l,nl,n,i,m,a,b:integer;
    used:array[1..100] of boolean;
procedure dfs(v:integer);
var i:integer;
begin
  used[v]:=true;
  for i:=1 to n do
    if not used[i] and g[v,i] then dfs(i);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  l:=0;
  nl:=0;
  for i:=1 to m do
    begin
      read(a,b);
      fillchar(used,sizeof(used),0);
      dfs(a);
      if used[b] then
          if l=0 then l:=i
          else
      else
        begin
          g[a,b]:=true;
          g[b,a]:=true;
          nl:=i;
        end;
    end;
  write(l,' ',nl);
end.