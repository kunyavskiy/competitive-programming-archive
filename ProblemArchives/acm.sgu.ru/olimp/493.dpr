{$APPTYPE CONSOLE}

uses
   Math;

var tree:array[1..1 shl 18] of integer;
    list,n,i,b:integer;
    a:array[1..100000] of integer;

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

procedure update(a,x:integer);
begin
  a:=a+list-1;
  tree[a]:=x;
  while a>1 do
    begin
      a:=a div 2;
      tree[a]:=tree[2*a]+tree[2*a+1];
    end;
end;

function rsq(l,r:integer):integer;
begin
   if l>r then
     begin
       result:=0;
       exit;
     end;
   l:=l+list-1;
   r:=r+list-1;
   result:=0;
   while (r-l>1) do
   begin
     if l and 1=1 then inc(result,tree[l]);
     if r and 1=0 then inc(result,tree[r]);
     l:=(l+1) shr 1;
     r:=(r-1) shr 1;
   end;
  result:=result+tree[l];
  if l<>r then result:=result+tree[r];
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
      read(b);
      a[b]:=i;
    end;
  maketree;
  for i:=1 to n div 2 do
    begin
      writeln(rsq(1,a[i]-1));
      update(a[i],0);
      writeln(rsq(a[n-i+1]+1,n));
      update(a[n-i+1],0);
    end;
 if n mod 2=1 then
    writeln(0);
end.