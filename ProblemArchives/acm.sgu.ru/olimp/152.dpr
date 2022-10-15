{$APPTYPE CONSOLE}
var a,b : array [1..15000] of integer;
    n,i,j:integer;
procedure QSort(left, right : integer);
var m, i, j, t : integer;
begin
  m := a[(left+right) div 2];
  i := left; j := right;
  repeat
    while a[i] < m do inc(i); {первый while}
    while a[j] > m do dec(j); {второй while}
    if i <= j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do read(b[i]);
for i:=1 to n do read(a[i]);
qsort(1,n);
for i:=1 to n do
begin
write(a[b[i]],' ');
for j:=b[i] to n-i do a[j]:=a[j+1];
end;
end.