{$APPTYPE CONSOLE}
{$O+,R+,q+}

uses
  Math;


var n,k,i,list,x,j,res:integer;
    tree:array[1..20000] of integer;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 read(n);
 list:=1;
 while list<n do
   list:=list*2;
 for i:=1 to n do
   read(tree[list+i-1]);
 for i:=list+n to list*2-1 do tree[i]:=0;
 for i:=list-1 downto 1 do
  tree[i]:=max(tree[2*i],tree[2*i+1]);
 read(k);
 for i:=1 to k do
 begin
   read(x);
   if tree[1]<x then continue;
   j:=1;
   while j<list do
    begin
     if tree[2*j]>=x then j:=2*j
     else j:=2*j+1;
    end;
   tree[j]:=tree[j]-x;
   while j>1 do
    begin
    j:=j div 2;
    tree[j]:=max(tree[2*j],tree[2*j+1])
    end;
  end;
 res:=0;
 for i:=list to list+n-1 do
 res:=res+tree[i];
 write(res);
end.