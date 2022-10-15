{$APPTYPE CONSOLE}
{$o+}
uses
  SysUtils;
const base=1 shl 20-1;
type int=longint;
      list =record
      s:string;
      x:int;
      next:int;
      end;
var  a:array[1..10000] of list;
     b:array[0..base] of integer;
     s1:string;
     ka,i,h,c,v:int;

procedure QSort(left, right :  integer);
var i, j, t : integer;
    m,t1:string;
begin
  m := a[random(right-left)+left].s;
  i := left; j := right;
  repeat
    while a[i].s < m do inc(i);
    while a[j].s > m do dec(j);
    if i <= j then
    begin
      t := a[i].x; a[i].x := a[j].x; a[j].x := t;
      t1 := a[i].s; a[i].s := a[j].s; a[j].s := t1;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;

function hash (var s:string):int;
var i:int;
    r:int;
begin
r:=0;
for i:=1 to length(s) do
r:=(r*239+ord(s[i])) and base;
hash:=r;
end;
procedure add (var l:int;var st:string);
begin
inc(ka);
a[ka].s:=st;
a[ka].next:=l;
a[ka].x:=1;
l:= ka;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
ka:=0;
v:=0;
while not eof do
begin
readln(s1);
inc(v);
h:=hash(s1);
if b[h]=0 then
begin
inc(ka);
b[h]:=ka;
a[ka].s:=s1;
a[ka].x:=1;
end
else
begin
c:=b[h];
while not((a[c].next=0) or (a[c].s=s1)) do c:=a[c].next;
if not(a[c].s=s1)  then add(b[h],s1)
else inc(a[c].x);
end;
end;
qsort(1,ka);
for i:=1 to ka do
begin
write(a[i].s,' ');
writeln((a[i].x/v)*100:0:4);
end;
end.