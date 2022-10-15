{$APPTYPE CONSOLE}

type event=record
       time,start,num:integer;
       end;

var events:array[1..200000] of event;
    list,n,m,i:integer;
    tree:array[1..(1 shl 18)] of integer;
    park:array[1..100000] of integer;
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

function findfirstdown(a:integer):integer;
begin
  if tree[a]=0 then
    begin
      result:=-1;
      exit;
    end;
  result:=a;
  while result<list do
    if tree[2*result]>0 then result:=2*result
    else result:=2*result+1;
  result:=result-list+1;
end;

function findfirstafter(a:integer):integer;
var k:integer;
begin
  a:=list+a-1;
  while true do
    begin
       k:=findfirstdown(a);
       if k<>-1 then
         begin
           result:=k;
           break;
         end;
       a:=(a+1) shr 1;
    end;
end;

procedure qsort(l,r:integer);
var m,i,j:integer;
    t:event;
begin
  m:=events[random(r-l+1)+l].time;
  i:=l; j:=r;
  repeat
    while events[i].time < m do inc(i);
    while events[j].time > m do dec(j);
    if i<=j then
    begin
      t:=events[i]; events[i]:=events[j]; events[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  maketree;
  for i:=1 to m do
    begin
      read(events[2*i-1].time);
      read(events[2*i].time);
      read(events[2*i-1].start);
      events[2*i].start:=0;
      events[2*i-1].num:=i;
      events[2*i].num:=i;
    end;
  qsort(1,2*m);
  for i:=1 to 2*m do
    if events[i].start=0 then update(park[events[i].num],1)
    else
      begin
        park[events[i].num]:=findfirstafter(events[i].start);
        update(park[events[i].num],0);
      end;
  for i:=1 to m do
    writeln(park[i]);
end.