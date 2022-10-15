{$APPTYPE CONSOLE}
{$O+}

type tablel=record
      v:int64;
      kol,next:integer;
      end;

const base=214398;

var g:array[1..3500] of tablel;
    a:array[1..3500] of integer;
    h:array[0..base-1] of integer;
    free,n,res,i,j:integer;
function hash(a:int64):integer;
var k:integer;
begin
  result:=0;
  k:=0;
  if a<0 then k:=-1;
  a:=abs(a);
  while a>0 do
    begin
      result:=(result*239+(a mod 10)) mod base;
      a:=a div 10;
    end;
  result:=result+k;
end;

procedure add(a:int64);
var l,k:integer;
begin
  k:=hash(a);
  l:=h[k];
  while l<>0 do
    begin
      if g[l].v=a then
        begin
          inc(g[l].kol);
          exit;
        end;
      l:=g[l].next;
    end;
  g[free].v:=a;
  g[free].kol:=1;
  g[free].next:=h[k];
  h[k]:=free;
  inc(free);
end;

function kolvo(a:int64):integer;
var k,l:integer;
begin
  k:=hash(a);
  l:=h[k];
  result:=0;
  while l<>0 do
    begin
      if g[l].v=a then
        begin
          result:=g[l].kol;
          exit;
        end;
      l:=g[l].next
    end;
end;




begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  free:=1;
  for i:=1 to n do
    begin
      read(a[i]);
      add(a[i]);
    end;
  res:=0;
  for i:=1 to n do
    for j:=1 to n do
    if i<>j then
      begin
        res:=res+kolvo(a[i]+a[j]);
        if a[i]=0 then dec(res);
        if a[j]=0 then dec(res);
      end;
  writeln(res);
end.