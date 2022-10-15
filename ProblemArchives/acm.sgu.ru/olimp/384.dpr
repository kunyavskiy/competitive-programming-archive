{$APPTYPE CONSOLE}

const maxlist=1 shl 13;

var k,l,list,n,m,i,z:integer;
    tree:array[1..2*maxlist-1] of integer;
    a:array[1..5000] of integer;



procedure update(x,k:integer);
begin
 x:=list+x-1;
 tree[x]:=k;
 while x>1 do
  begin
    x:=x div 2;
    tree[x]:=tree[2*x]+tree[2*x+1];
  end;
end;

procedure nultree;
var i:integer;
begin
  list:=1;
  while list<m do
    list:=list*2;
  for i:=1 to m do
   update(i,1);
  for i:=m+1 to list do
   tree[i+list-1]:=0;
end;

procedure zapros(x,k:integer);
begin
  if a[x]=0 then
   begin
     a[x]:=k;
     update(x,0);
     exit;
   end;
  x:=1;
  if tree[1]=0 then exit;
  while x<list do
   begin
     if tree[2*x]>0 then x:=2*x
     else x:=2*x+1;
   end;
  x:=x-list+1;
  a[x]:=k;
  update(x,0);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k);
  for l:=1 to k do
    begin
    fillchar(a,sizeof(a),0);
    fillchar(tree,sizeof(tree),0);
    read(n,m);
    nultree;
    for i:=1 to n do
      begin
      read(z);
      zapros(z,i);
      end;
    for i:=1 to m do
      write(a[i],' ');
    writeln;
    end;
end.