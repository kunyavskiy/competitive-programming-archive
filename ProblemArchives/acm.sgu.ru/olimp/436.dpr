{$APPTYPE CONSOLE}

uses
  Math;

type abcd=record
          ver,next:integer;
          end;

var k,i,kol,n,a,m,b,j:integer;
    g:array[1..240] of abcd;
    h:array[1..16] of integer;
    free:integer;
    used:array[1..16] of boolean;
procedure add(a,b:integer);
begin
  inc(free);
  g[free].ver:=b;
  g[free].next:=h[a];
  h[a]:=free;
  inc(free);
  g[free].ver:=a;
  g[free].next:=h[b];
  h[b]:=free;
end;


function bit(a:integer):integer;
var i:integer;
begin
  result:=0;
  for i:=0 to 15 do
    if (a and (1 shl i))>0 then inc(result);
end;

procedure dfs(v:integer;mask:integer);
var l:integer;
begin
  if mask and (1 shl (v-1))>0 then
    begin
      used[v]:=true;
      exit;
    end;
  inc(kol);
  used[v]:=true;
  l:=h[v];
  while l<>0 do
    begin
      if not used[g[l].ver] then dfs(g[l].ver,mask);
      l:=g[l].next;
    end;
end;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(n,m,k);
   for i:=1 to m do
     begin
       read(a,b);
       add(a,b);
     end;
   for i:=1 to trunc(power(2,n)) do
     begin
       b:=bit(i);
       if b=k then
         begin
           kol:=0;
           fillchar(used,sizeof(used),false);
           for j:=0 to n-1 do
              if i and (1 shl j)=0 then
                begin
                  dfs(j+1,i);
                  break;
                end;
           if kol<n-k then
               begin
                 for j:=0 to n-1 do
                   if (i and (1 shl j))<>0 then write(j+1,' ');
                 close(input);
                 close(output);
                 halt;
               end;
         end;
     end;
   write(0);
end.