{$APPTYPE CONSOLE}
uses
  SysUtils;
type uch=record
    name:string;
    h:integer;
    end;
var a:array[1..5000] of uch;
    n,i:integer;
    s:string;
    c:char   ;
procedure QSort(left, right : integer);
var m, i, j, t : integer;
    t1:string;
begin
  m := a[(left+right) div 2].h;
  i := left; j := right;
  repeat
    while a[i].h < m do inc(i); {первый while}
    while a[j].h > m do dec(j); {второй while}
    if i <= j then
    begin
      t := a[i].h; a[i].h := a[j].h; a[j].h := t;
       t1 := a[i].name; a[i].name := a[j].name; a[j].name := t1;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
readln(n);
for i:=1 to n do
begin
read(c);
s:='';
while not (c=' ') do
begin
s:=s+c;
read(c);
end;
a[i].name:=s;
readln(a[i].h);
end;
qsort(1,n);
for i:=1 to n do writeln(a[i].name);
end.