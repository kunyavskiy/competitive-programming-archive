{$APPTYPE CONSOLE}

uses
  SysUtils;

var s:array[1..400] of integer;
    g:array[1..200,1..200] of boolean;
    h,a,b,c,n,m,i,a1,b1:integer;
    q:boolean;
    used:array[1..200] of boolean;

procedure push(x:integer);
begin
  inc(h);
  s[h]:=x;
end;

procedure pop;
begin
 dec(h);
end;

procedure dfs (v:integer);
var i:integer;
begin
 push(v);
 if v=c then q:=true;
 used[v]:=true;
 for i:=1 to n do
  if (g[v,i])and not used[i]  and not q then dfs(i);
 if not q then pop;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,c);
  read(n,m);
  for i:=1 to m do
    begin
    read(a1,b1);
    g[a1,b1]:=true;
    g[b1,a1]:=true;
    end;
  h:=0;
  dfs(a);
  if not q then
  begin
    write('NO');
    close(input);
    close(output);
    halt;
  end;
  fillchar(used,sizeof(used),false);
  q:=false;
  a:=c;
  c:=b;
  pop;
  dfs(a);
  if not q then
  begin
    write('NO');
    close(input);
    close(output);
    halt;
  end;
  writeln('YES');
  write(h,' ');
  for i:=1 to h do
   write(s[i],' ');
end.