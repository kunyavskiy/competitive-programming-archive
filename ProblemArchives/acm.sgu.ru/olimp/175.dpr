{$APPTYPE CONSOLE}

uses
  SysUtils;

type treeel=record
      x,y:int64;
      l,r:integer;
      end;
     robot=record
       c:int64;
       x:integer;
       end;


var tree:array[-1..100000] of treeel;
    head,i,n,m,l,r:integer;
    res:int64;
    rob:array[1..10000] of robot;

function merge(l,r:integer):integer;
begin
  if l=-1 then
    begin
      result:=r;
      exit;
    end;
  if r=-1 then
    begin
      result:=l;
      exit;
    end;
  if (tree[l].y>tree[r].y) then
    begin
       result:=l;
       tree[l].r:=merge(tree[l].r,r);
       exit;
    end;
  result:=r;
  tree[r].l:=merge(l,tree[r].l);
end;

procedure split(v:integer;var l,r:integer;x:int64);
begin
  if v=-1 then
    begin
      l:=-1;
      r:=-1;
      exit;
    end;
  if tree[v].x<x then
      begin
       l:=v;
       split(tree[v].r,tree[v].r,r,x)
      end
  else
      begin
       r:=v;
       split(tree[v].l,l,tree[v].l,x);
      end;
end;

procedure swap(var a,b:robot);
var t:robot;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure deletefirstsmaller(var v:integer);
begin
  if tree[v].l=-1 then
    v:=tree[v].r
  else
    deletefirstsmaller(tree[v].l);
end;

procedure qsort(l,r:integer);
var i,j,m:integer;
begin
  i:=l;
  j:=r;
  m:=rob[random(r-l+1)+1].c;
  while i<=j do
    begin
      while rob[i].c>m do inc(i);
      while rob[j].c      <m do dec(j);
      if i<=j then
        begin
          swap(rob[i],rob[j]);
          inc(i);
          dec(j);
        end;
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  randomize;
  read(n,m);
  for i:=1 to n do
      read(rob[i].x,rob[i].c);
  qsort(1,n);
  head:=-1;
  res:=0;
  for i:=1 to m do
    begin
      read(tree[i].x);
      tree[i].y:=random(56789);
      tree[i].l:=-1;
      tree[i].r:=-1;
      split(head,l,r,tree[i].x);
      l:=merge(l,i);
      head:=merge(l,r);
    end;
  for i:=1 to n do
    begin
      split(head,l,r,rob[i].x);
      if r<>-1 then
       begin
        res:=res+rob[i].c;
        deletefirstsmaller(r);
       end;
      head:=merge(l,r);
    end;
  write(res);

end.