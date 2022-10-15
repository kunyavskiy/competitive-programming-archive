{$APPTYPE CONSOLE}

uses
  Math;

type treeel=record
       x,y,l,r,kol:integer;
       end;
     diag=record
       s,e,len:integer;
       prochas:boolean;
       end;

var tree:array[-1..5000] of treeel;
    a:array[1..5000] of diag;
    n,head,i,k,l,m,r,ka:integer;
    answer:array[1..5000] of integer;

function makediag:diag;
var a,b:integer;
begin
  read(a,b);
  result.s:=min(a,b);
  result.e:=max(a,b);
  if result.e-result.s<result.s+n+1-result.e then
    begin
      result.len:=result.e-result.s+1;
      result.prochas:=true;
    end
  else
    begin
      result.len:=result.s+n+1-result.e;
      result.prochas:=false;
    end;
end;


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
  if tree[l].y>tree[r].y then
    begin
      result:=l;
      tree[l].r:=merge(tree[l].r,r);
      tree[result].kol:=tree[tree[result].l].kol+tree[tree[result].r].kol+1;
      exit;
    end;
  result:=r;
  tree[r].l:=merge(l,tree[r].l);
  tree[result].kol:=tree[tree[result].l].kol+tree[tree[result].r].kol+1;
end;

procedure split(v,x:integer;var l,r:integer);
begin;
  if v=-1 then
    begin
      l:=-1;
      r:=-1;
      exit;
    end;
  if tree[v].x<x then
    begin
      l:=v;
      split(tree[v].r,x,tree[v].r,r);
      tree[v].kol:=tree[tree[v].l].kol+tree[tree[v].r].kol+1;
      exit;
    end;
  r:=v;
  split(tree[v].l,x,l,tree[v].l);
  tree[v].kol:=tree[tree[v].l].kol+tree[tree[v].r].kol+1;
end;

procedure QSort(l,r:integer);
var m,i,j:integer;
    t:diag;
begin
  m:=a[random(r-l+1)+l].len;
  i:=l; j:=r;
  repeat
    while a[i].len<m do inc(i);
    while a[j].len>m do dec(j);
    if i<=j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  randomize;
  head:=-1;
  for i:=1 to n do
    begin
      tree[i].x:=i;
      tree[i].y:=random(563802);
      tree[i].l:=-1;
      tree[i].r:=-1;
      tree[i].kol:=1;
      head:=merge(head,i);
    end;
  read(k);
  for i:=1 to k do
     a[i]:=makediag;
  qsort(1,k);
  for i:=1 to k do
    if a[i].prochas then
      begin
        split(head,a[i].s+1,l,m);
        split(m,a[i].e,m,r);
        inc(ka);
        answer[ka]:=tree[m].kol+2;
        head:=merge(l,r);
      end
    else
      begin
         split(head,a[i].s,l,m);
         split(m,a[i].e+1,m,r);
         inc(ka);
         answer[ka]:=tree[l].kol+tree[r].kol+2;
         head:=m;
      end;
  inc(ka);
  answer[ka]:=tree[head].kol;
  writeln(ka);
  for i:=1 to ka do
    write(answer[i],' ')
end.