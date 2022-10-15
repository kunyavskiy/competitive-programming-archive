{$APPTYPE CONSOLE}



uses
  Math;

type town=record
         x,y,num,kol:integer;
         end;
var  a:array[1..1000] of town;
     n,j,i:integer;

procedure QSort(left, right : integer);
var m, i, j : integer;
    t:town;
begin
  m := a[(left+right) div 2].x;
  i := left; j := right;
  repeat
    while a[i].x < m do inc(i); {&#239;&#229;&#240;&#226;&#251;&#233; while}
    while a[j].x > m do dec(j); {&#226;&#242;&#238;&#240;&#238;&#233; while}
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
  for i:=1 to n do
    begin
      read(a[i].x,a[i].y);
      a[i].num:=i;
    end;
  qsort(1,n);
  for i:=1 to n do
     begin
       a[i].kol:=-1;
       if a[i].num=1 then
         a[i].kol:=0;
       for j:=1 to i-1 do
         if (a[j].x<a[i].x) and (a[j].y>a[i].y) and (a[j].kol<>-1) then
            a[i].kol:=max(a[i].kol,a[j].kol+1);
       if a[i].num=n then
         begin
           if a[i].kol>0 then write(a[i].kol-1)
           else write('No way');
           exit;
         end
     end;
end.