{$APPTYPE CONSOLE}

uses
  SysUtils;

type borel=record
         next:array['A'..'z'] of integer;
         kol:integer;
         end;
    abcd=record
       st:string;
       next:integer;
       end;


var bor:array[1..5000] of borel;
    kbor,i,j,k,free:integer;
    s,sc:string;
    tabl:array[1..5000] of abcd;
    head:array[0..4937] of integer;

function hash(s:string):integer;
var i:integer;
begin
  result:=ord(s[1]);
  for i:=2 to length(s) do
    result:=(result*37+ord(s[i])) mod 4937;
end;

procedure addtotabl(s:string);
var h,l:integer;
begin
  h:=hash(s);
  l:=head[h];
  while l<>0 do
    begin
      if tabl[l].st=s then exit;
      l:=tabl[l].next;
    end;
  inc(free);
  tabl[free].st:=s;
  tabl[free].next:=head[h];
  head[h]:=free;
end;



function gooradd(v:integer;c:char):integer;
begin
  if bor[v].next[c]=-1 then
    begin
      inc(kbor);
      bor[v].next[c]:=kbor;
      fillchar(bor[kbor].next,sizeof(bor[kbor].next),-1);
      bor[kbor].kol:=1;
      result:=kbor;
      exit;
    end;
  result:=bor[v].next[c];
  inc(bor[result].kol);
end;

procedure add(s:string);
var t,i:integer;
begin
  t:=1;
  for i:=1 to length(s) do
    t:=gooradd(t,s[i]);
end;

function go(v:integer;c:char):integer;
begin
  result:=bor[v].next[c];
end;

function isonce(s:string):boolean;
var t,i:integer;
begin
  t:=1;
  result:=false;
  for i:=length(s) downto 1 do
    begin
      t:=go(t,s[i]);
      if t=-1 then exit;
    end;
  result:=bor[t].kol=1;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  sc:=s;
  kbor:=1;
  fillchar(bor[kbor].next,sizeof(bor[kbor].next),-1);
  for i:=1 to length(s) do
    begin
      add(sc);
      delete(sc,1,1);
    end;
  k:=0;
  for i:=1 to length(s) do
    for j:=1 to length(s)-i+1 do
      addtotabl(copy(s,i,j));
  for i:=1 to free do
    if isonce(tabl[i].st) then inc(k);
  write(k);
end.