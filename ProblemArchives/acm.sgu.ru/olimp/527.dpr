{$APPTYPE CONSOLE}

uses
  SysUtils;


type abcd=record
       frver,tover,len,num:integer;
       end;
     reb=record
         v,num,next:integer;
         end;
     dostel=array[1..315] of integer;

var spis:array[1..200000] of abcd;
    g:array[1..200000] of reb;
    head:array[1..10000] of integer;
    deleted:array[1..200000] of boolean;
    top:array[1..10000] of integer;
    n,m,i,koldel,free,ktop:integer;
    dost:array[1..10000] of dostel;
    used:array[1..10000] of boolean;


procedure add(spisnum:integer);
var a,b:integer;
begin
   inc(free);
   a:=spis[spisnum].frver;
   b:=spis[spisnum].tover;
   g[free].next:=head[a];
   g[free].num:=spis[spisnum].num;
   g[free].v:=b;
   head[a]:=free;
end;

procedure deletereb(a:integer);
begin
  if deleted[a] then exit;
  deleted[a]:=true;
  inc(koldel);
end;

procedure orarray(var a:dostel; b:dostel);
var i:integer;
begin
  for i:=1 to 315 do
    a[i]:=a[i] or b[i];
end;

procedure topsort(v:integer);
var l:integer;
begin
  used[v]:=true;
  l:=head[v];
  while l<>0 do
    begin
      if not used[g[l].v] then topsort(g[l].v);
      l:=g[l].next;
    end;
  top[v]:=ktop;
  dec(ktop);
end;

function isdost(vs,ve:integer):boolean;
var ve32:integer;
begin
  ve32:=dost[vs,((ve-1) shr 5)+1];
  ve:=(ve-1) and 31;
  result:=(ve32 and (1 shl ve))<>0
end;

procedure markdost(v:integer);
var ve32:integer;
begin
  ve32:=((v-1) shr 5)+1;
  dost[v,ve32]:=dost[v,ve32] or (1 shl ((v-1) and 31));
end;



function dfs(v:integer):dostel;
var l,nv:integer;
begin
  if used[v] then
   begin
     result:=dost[v];
     exit;
   end;
  used[v]:=true;
  l:=head[v];
  markdost(v);
  while l<>0 do
    begin
      nv:=g[l].v;
      if isdost(v,nv) then
        deletereb(g[l].num)
      else orarray(dost[v],dfs(nv));
      l:=g[l].next;
    end;
  result:=dost[v];
end;

function less(a,b:abcd):boolean;
begin
   if a.tover<b.tover then
     begin
       result:=true;
       exit;
     end;
   if a.tover>b.tover then
     begin
       result:=false;
       exit;
     end;
   if a.frver<b.frver then
     begin
       result:=true;
       exit;
     end;
   if a.frver>b.frver then
     begin
       result:=false;
       exit;
     end;
   result:=a.len<b.len;
end;

function less2(a,b:abcd):boolean;
begin
   if a.tover>b.tover then
     begin
       result:=true;
       exit;
     end;
   if a.tover<b.tover then
     begin
       result:=false;
       exit;
     end;
   if a.frver>b.frver then
     begin
       result:=true;
       exit;
     end;
   if a.frver<b.frver then
     begin
       result:=false;
       exit;
     end;
   result:=a.len<b.len;
end;

procedure swap(var a,b:abcd);
var t:abcd;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m:abcd;
begin
  m:=spis[random(r-l+1)+l];
  i:=l;
  j:=r;
  while i<=j do
    begin
      while less(spis[i],m) do inc(i);
      while less(m,spis[j]) do dec(j);
      if i<=j then
        begin
          swap(spis[i],spis[j]);
          dec(j);
          inc(i);
        end;
    end;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);

end;


procedure qsort2(l,r:integer);
var i,j:integer;
    m:abcd;
begin
  m:=spis[random(r-l+1)+l];
  i:=l;
  j:=r;
  while i<=j do
    begin
      while less2(spis[i],m) do inc(i);
      while less2(m,spis[j]) do dec(j);
      if i<=j then
        begin
          swap(spis[i],spis[j]);
          dec(j);
          inc(i);
        end;
    end;
  if l<j then qsort2(l,j);
  if i<r then qsort2(i,r);

end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to m do
    begin
      read(spis[i].frver);
      read(spis[i].tover);
      read(spis[i].len);
      spis[i].num:=i;
    end;
  qsort(1,m);
  add(1);
  for i:=2 to m do
    if (spis[i].frver<>spis[i-1].frver) or (spis[i].tover<>spis[i-1].tover) then
       add(i)
    else deletereb(spis[i].num);
  ktop:=n;
  for i:=1 to n do
   if not used[i] then
     topsort(i);;
  free:=0;
  fillchar(head,sizeof(head),0);
  for i:=1 to m do
    begin
      spis[i].frver:=top[spis[i].frver];
      spis[i].tover:=top[spis[i].tover];
    end;
  qsort2(1,m);
  add(1);
  for i:=2 to m do
    if (spis[i].frver<>spis[i-1].frver) or (spis[i].tover<>spis[i-1].tover) then
       add(i);
  fillchar(used,sizeof(used),false);
  for i:=1 to n do
  if not used[i] then  dfs(i);
  writeln(koldel);
  for i:=1 to m do
    if deleted[i] then write(i,' ');
end.