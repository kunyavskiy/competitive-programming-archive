{$APPTYPE CONSOLE}

var used:array[1..100] of integer;
    g:array[1..100,1..100] of boolean;
    st:array[1..100] of integer;
    n,h,i:integer;

procedure readgraf;
var m,a,i,j:integer;
begin
  read(n);
  for i:=1 to n do
    begin
     read(m);
     for j:=1 to m do
       begin
         read(a);
         g[a,i]:=true;
       end;
    end;
  h:=0;
end;

procedure push(x:integer);
begin
 inc(h);
 st[h]:=x;
end;

procedure pop;
begin
 write(st[h],' ');
 dec(h);
end;

procedure topsort (v:integer);
var i:integer;
begin
 if used[v]=1 then
   begin
    write(0);
    close(input);
    close(output);
    halt;
   end;
 if used[v]=2 then exit;
 used[v]:=1;
 for i:=1 to n do
  if g[v,i] then topsort(i);
 used[v]:=2;
 push(v);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readgraf;
  for i:=1 to n do
  if used[i]=0 then topsort(i);
  while h>0 do pop;
end.