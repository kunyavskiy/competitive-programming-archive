{$APPTYPE CONSOLE}


type reb=record
      v,next,time:integer;
      end;

var tree:array[1..35000] of integer;
    h,from:array[1..10000] of integer;
    g:array[1..20000] of reb;
    used:array[1..10000] of boolean;
    free,list,n,m,a,b,t,i:integer;

function Min(const A, B: Integer): Integer;
begin
  if A < B then
    Result := A
  else
    Result := B;
end;

procedure add(x,x1,t:integer);
begin
 inc(free);
 g[free].v:=x;
 g[free].next:=h[x1];
 h[x1]:=free;
 g[free].time:=t;
 inc(free);
 g[free].v:=x1;
 g[free].next:=h[x];
 h[x]:=free;
 g[free].time:=t;
end;

procedure print(x:integer);
begin
  if x=0 then
    begin
     write('No solution');
     close(input);
     close(output);
     halt;
    end;
  if x<>1 then print(from[x]);
  write(x,' ')
end;

procedure update(num,p,t:integer);
var x:integer;
begin
  x:=tree[list+p-1]+t;
  if tree[list+num-1]<=x then exit;
  from[num]:=p;
  num:=list+num-1;
  tree[num]:=x;
  while num>1 do
   begin
    num:=num shr 1 ;
    tree[num]:=min(tree[2*num],tree[2*num+1]);
   end;
end;

procedure upupdate(num:integer);
var x:integer;
begin
  x:=maxlongint;
  num:=list+num-1;
  tree[num]:=x;
  while num>1 do
   begin
    num:=num shr 1 ;
    tree[num]:=min(tree[2*num],tree[2*num+1]);
   end;
end;

function findmin:integer;
begin
  result:=1;
  while result<list do
    begin
      if tree[2*result]<tree[2*result+1] then result:=result*2
      else result:=result*2+1;
    end;
  result:=result-list+1;
end;

procedure maketree;
var i:integer;
begin
  list:=1;
  while list<n do list:=list*2;
  for i:=list to list+n-1  do
    tree[i]:=maxlongint div 2;
  for i:=list+n to 2*list-1 do
    tree[i]:=maxlongint;
  tree[list]:=0;
  for i:=list-1 downto 1 do
    tree[i]:=min(tree[2*i],tree[2*i+1]);
end;



procedure dikstra;
var i,num,l:integer;
begin
  for i:=1 to n-1 do
    begin
      num:=findmin;
      if tree[list+num-1]>=maxlongint div 2 then exit;
      l:=h[num];
      used[num]:=true;
      while l<>0 do
       begin
        if not used[g[l].v] then update(g[l].v,num,g[l].time);
        l:=g[l].next;
       end;
      upupdate(num);
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  free:=0;
  fillchar(h,sizeof(h),0);
  fillchar(from,sizeof(from),0);
  for i:=1 to m do
   begin
     read(a,b,t);
     add(a,b,t);
   end;
  maketree;
  dikstra;
  print(n);
end.