{$APPTYPE CONSOLE}
{$r-,Q-}

uses
  SysUtils, Math;



var g:array[1..10000] of record
                     v:integer;
                     next:integer;
                     end;
    h:array[1..10001] of integer;
    used:array[1..10001] of boolean;
    free,maxn,a,b,i,l:integer;
procedure add (x,i:integer);
  begin
   g[free].v:=x;
   g[free].next:=h[i];
   h[i]:=free;
   inc(free);
  end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(b);
  maxn:=b;
  free:=1;
  used[b]:=true;
  fillchar(h,sizeof(h),0);
  for i:=1 to 9999 do
  begin
  g[i].v:=0;
  g[i].next:=0;
  end;
  while not eof do
  begin
  a:=b;
  read(b);
  if (not used[b]) and (b<>0) then  add(b,a);
  maxn:=max(maxn,b);
  used[b]:=true;
  end;
  for i:=1 to maxn do
  begin
   l:=h[i];
   while l<>0 do
   begin
     write(g[l].v,' ');
     l:=g[l].next;
   end;
   writeln(0);
  end;
end.