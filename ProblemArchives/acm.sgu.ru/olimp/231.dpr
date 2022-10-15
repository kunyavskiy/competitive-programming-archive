{$APPTYPE CONSOLE}

type sps=record
        id:string;
        num:integer;
        next:integer;
        end;

const base=(1 shl 15)-1;


var i,list,hashnum,n,m,free:integer;
    tree:array[1..33000] of integer;
    tabl:array[1..100000] of sps;
    head:array[0..base] of integer;
    s:string;

function hash1(var s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*137+ord(s[i])) mod base
end;

function hash2(var s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*163+ord(s[i])) mod base
end;

function hash3(var s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*181+ord(s[i])) mod base
end;

function hash4(var s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*113+ord(s[i])) mod base
end;

function hash5(var s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*191+ord(s[i])) mod base
end;

function hash(var s:string):integer;
begin
  case hashnum of
  1:hash:=hash1(s);
  2:hash:=hash2(s);
  3:hash:=hash3(s);
  4:hash:=hash4(s);
  5:hash:=hash5(s);
  end;
end;

procedure maketree;
var i:integer;
begin
  list:=1;
  while list<n do
     list:=list*2;
  for i:=list to list+n-1 do tree[i]:=1;
  for i:=list+n to 2*list-1 do tree[i]:=0;
  for i:=list-1 downto 1 do
     tree[i]:=tree[2*i]+tree[2*i+1];
end;

procedure update(x,y:integer);
begin
  x:=x+list-1;
  tree[x]:=y;
  while x>1 do
   begin
     x:=x div 2;
     tree[x]:=tree[2*x]+tree[2*x+1];
   end;
end;

function freenum:integer;
begin
  result:=1;
  while result<list do
    if tree[2*result]=0 then result:=2*result+1
    else result:=result*2;
  result:=result-list+1;
  update(result,0);
end;

procedure getmem( s:string);
var k,l:integer;
begin
  k:=hash(s);
  l:=head[k];
  while l<>0 do
    begin
    if tabl[l].id=s then
      begin
        tabl[l].num:=freenum;
        writeln(tabl[l].num);
        exit;
      end;
    l:=tabl[l].next;
    end;
  tabl[free].id:=s;
  tabl[free].num:=freenum;
  tabl[free].next:=head[k];
  writeln(tabl[free].num);
  head[k]:=free;
  inc(free);
end;

procedure clear(s:string);
var k,l:integer;
begin
  k:=hash(s);
  l:=head[k];
  while l<>0 do
  begin
    if tabl[l].id=s then
      begin
        update(tabl[l].num,1);
        exit;
      end;
    l:=tabl[l].next;
  end;
end;



begin
  randomize;
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  maketree;
  hashnum:={random(5)+}1;
  free:=1;
  for i:=1 to m do
    begin
      readln(s);
      if copy(s,1,5)='CLEAR' then clear(copy(s,7,length(s)-7))
      else getmem(copy(s,1,length(s)-11))
    end;
end.