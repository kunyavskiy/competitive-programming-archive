var a:array[1..50] of integer;
    n,s1,s2,i:integer;
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
s1:=0;
s2:=0;
for i:=1 to n do read(a[i]);
qsort(1,n);
for i:=1 to n div 2 do
begin
s1:=s1+a[n-2*i+2];
s2:=s2+a[n-2*i+1];
end;
if n mod 2 =1 then s1:=s1+a[1];
write(abs(s1-s2));
end.