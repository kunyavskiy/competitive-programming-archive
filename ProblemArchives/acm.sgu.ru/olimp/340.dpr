{$APPTYPE CONSOLE}
var p:array[1..100] of record
                       x,y,r:integer;
                       end;
   g:array[1..100,1..100] of boolean;
   w:array[1..100] of real;
   n,m,j,i,a,b:integer;
   eps:real;
function maygetvrash(a:integer;b:real):boolean;
begin
  if (w[a]<>0) and (w[a]-b>=eps) then
     begin
       write('DO NOT TURN IT ON!');
       close(input);
       close(output);
       halt;
     end;
  if abs(w[a]-b)<eps then result:=false
  else
   begin
    w[a]:=b;
    result:=true;
   end;
end;

procedure dfs(v:integer;wv:real);
var i:integer;
begin
  for i:=1 to n do
    begin
    if (i<>v) and (p[v].x=p[i].x) and (p[v].y=p[i].y) and maygetvrash(i,wv) then dfs(i,wv);
    if g[v,i] and maygetvrash(i,wv*p[v].r/p[i].r) then dfs(i,wv*p[v].r/p[i].r)
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m,j);
  for i:=1 to n do
    read(p[i].x,p[i].y,p[i].r);
  for i:=1 to m do
    begin
      read(a,b);
      g[a,b]:=true;
      g[b,a]:=true;
    end;
  w[j]:=60000;
  eps:=0.0000000001;
  dfs(j,60000);
  for i:=1 to n do
    begin
      if w[i]=0 then writeln('IDLE')
      else writeln(trunc(w[i]));
    end;
end.