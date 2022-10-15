{$APPTYPE CONSOLE}

uses
   Math;

type type1=record
        ver,next:integer;
        end;
     type2=record
        c,num:integer;
        end;
var p:array[1..7500] of integer;
    g:array[1..15000] of type1;
    a:array[1..7500] of type2;
    used:array[1..7500] of boolean;
    h:array[1..7500] of integer;

    n,i,k,j,l,free,t:integer;

procedure add(a,b:integer);
begin
  inc(free);
  g[free].next:=h[a];
  g[free].ver:=b;
  h[a]:=free;
end;

function root(a:integer):integer;
begin
  if p[a]=a then
    begin
      result:=a;
      exit;
    end;
  result:=root(p[a]);
  p[a]:=result;
end;

procedure union(a,b:integer);
begin
  a:=root(a);
  b:=root(b);
  if a<>b then
  p[b]:=a;
end;

procedure swap(var a,b:type2);
var t:type2;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure dfs(v:integer);
var l:integer;
begin
  used[v]:=true;
  l:=h[v];
  while l<>0 do
    begin
     if not used[g[l].ver] then dfs(g[l].ver);
      l:=g[l].next;
    end;
end;


procedure qsort(l,r:integer);
var m,i,j:integer;
begin
  m:=a[random(r-l+1)+l].c;
  i:=l; j:=r;
  repeat
    while a[i].c < m do inc(i);
    while a[j].c > m do dec(j);
    if i<=j then
    begin
      swap(a[i],a[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end; 
procedure qsortnum(l,r:integer);
var m,i,j:integer;
begin
  m:=a[random(r-l+1)+l].num;
  i:=l; j:=r;
  repeat
    while a[i].num < m do inc(i);
    while a[j].num > m do dec(j);
    if i<=j then
    begin
      swap(a[i],a[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsortnum(l,j);
  if i<r then qsortnum(i,r);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  
  read(n);
  for i:=1 to n do
    begin
       read(a[i].c);
       if a[i].c=0 then a[i].c:=maxlongint div 2;
       a[i].num:=i;
       read(k);
       for j:=1 to k do
         begin
            read(l);
            add(i,l);
         end;
    end;
  for i:=1 to n do
    p[i]:=i;
  qsort(1,n);
  for i:=1 to n do
   if p[a[i].num]=a[i].num then
    begin
      if a[i].c=maxlongint div 2 then break;
      fillchar(used,sizeof(used),false);
      dfs(a[i].num);
      used[a[i].num]:=false;
      for j:=1 to n do
        if used[j] and (p[j]=j) then union(a[i].num,j);
    end;
   k:=0;
   t:=0;
   qsortnum(1,n);
   for i:=1 to n do
     if p[i]=i then
     begin
       if a[i].c=maxlongint div 2 then
         begin
           write(-1);
           close(input);
           close(output);
           halt;
         end;
       k:=k+1;
       t:=t+a[i].c;
     end;
   writeln(t);
   writeln(k);
   for i:=1 to n do
     if p[i]=i then write(i,' ');
end.