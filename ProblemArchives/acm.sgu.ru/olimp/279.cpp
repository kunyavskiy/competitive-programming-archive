{$APPTYPE CONSOLE}
uses
  SysUtils;
var n,m,a,b,i:integer;
    used:array[1..100] of boolean;
    c:boolean;
    g:array[1..100,1..100] of boolean;
procedure go (v:integer);
var j:integer;
begin
if used[v] then
begin
c:=false;
exit;
end;
used[v]:=true;
for j:=1 to n do
if g[v,j] then begin g[j,v]:=false; g[v,j]:=false; go(j); end;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(m);
c:=true;
for i:=1 to m do
begin
read(a);
read(b);
g[a,b]:=true;
g[b,a]:=true;
end;
go(1);
for i:=1 to n do c:= c and used[i];
if c then write('YES')
else write('NO')
end.