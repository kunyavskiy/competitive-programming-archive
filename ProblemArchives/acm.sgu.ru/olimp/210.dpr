{$APPTYPE CONSOLE}
{$H+}

uses
  SysUtils;

var  tree:array[1..2 shl 17] of integer;
     list,n,i:integer;

procedure maketree;
var i:integer;
begin
  list:=1;
  while list<n do list:=list*2;
  for i:=list to list+n-1 do
    tree[i]:=1;
  for i:=list+n to 2*list-1 do
    tree[i]:=0;
  for i:=list-1 downto 1 do
    tree[i]:=tree[2*i]+tree[2*i+1];
end;

function uppdate(x:integer):boolean;
var i,v,xc,k:integer;
begin
  result:=x<tree[1];
  xc:=x;
  k:=0;
  for i:=1 to n do
   begin
    v:=1;
    x:=i*xc-k;
    if x>tree[1] then break;
    while v<list do
      if x<=tree[2*v] then v:=2*v
      else
        begin
          x:=x-tree[2*v];
          v:=2*v+1;
        end;
    inc(k);
    tree[v]:=0;
    while v>1 do
     begin
      v:=v div 2;
      tree[v]:=tree[2*v]+tree[2*v+1];
     end;
   end;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  maketree;
  i:=2;
  while uppdate(i) do inc(i);
  for i:=1 to n do
    if tree[list+i-1]=1 then write(i,' ');
end.