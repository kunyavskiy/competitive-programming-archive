{$APPTYPE CONSOLE}
{$R+,Q+}

uses
  Math;

type reb=record
         s,e,c:integer;
         end;
var color:array[1..100] of integer;
    n,x,m,i,k:integer;
    a:array[1..5000] of reb;

procedure union(x,y:integer);
var t,i:integer;
begin
  t:=color[x];
  for i:=1 to n do
   if color[i]=t then color[i]:=color[y];
end;

function findmin(m,x:integer):integer;
var i,mi,num:integer;
begin
  mi:=maxlongint;
  num:=0;
  for i:=1 to m do
    if (color[a[i].s]<>color[a[i].e]) and (a[i].c<mi) then
      begin
       mi:=a[i].c;
       num:=i;
      end;
  if num=0 then begin findmin:=maxlongint div 2; exit; end;
  union(a[num].s,a[num].e);
  findmin:=a[num].c;
end;

function krascal(m,x:integer):integer;
var i:integer;
begin
  if m=0 then begin result:=maxlongint; exit; end;
  for i:=1 to n do
    color[i]:=i;
  result:=0;
  for i:=1 to n-1-x do
   begin
    result:=result+findmin(m,x);
    if result>=maxlongint div 2 then
      begin
        result:=maxlongint;
        exit;
      end;
   end;
end;

procedure swap(var a,b:reb);
var t:reb;
begin
  t:=a;
  a:=b;
  b:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,x,m);
  for i:=1 to m do
    read(a[i].s,a[i].e,a[i].c);
  i:=1;
  k:=0;
  while i<=m-k do
   begin
     if (a[i].e=x) or (a[i].s=x) then begin swap(a[i],a[m-k]); inc(k); end
     else inc(i);
   end;
  if (n=1) or (n=2) then write(0) else
  write(min(krascal(m,0),krascal(m-k,1)));
end.