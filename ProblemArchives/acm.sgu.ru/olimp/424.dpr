{$APPTYPE CONSOLE}
{{$O-}

type abcd=record
        kol,num:integer;
        ver:array[0..49] of boolean;
        end;


var pred:array[0..50] of abcd;
    rod:array[0..50] of integer;
    n,i,j,a:integer;
procedure qsort(l,r:integer);
var m,i,j:integer;
    t:abcd;
begin
  m:=pred[random(r-l+1)+l].kol;
  i:=l; j:=r;
  repeat
    while pred[i].kol<m do inc(i);
    while pred[j].kol>m do dec(j);
    if i<=j then
    begin
      t:=pred[i]; pred[i]:=pred[j]; pred[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  dec(n);
  for i:=0 to n do
   begin
    pred[i].kol:=0;
    pred[i].num:=i;
    for j:=0 to n do
    begin
      read(a);
      if not pred[i].ver[a] then inc(pred[i].kol);
      pred[i].ver[a]:=true;
    end;
   end;
  qsort(0,n);
  rod[pred[0].num]:=-1;
  for i:=1 to n do
      for j:=0 to n do
         if (pred[i].ver[pred[j].num]) and (pred[j].kol=pred[i].kol-1) then
           rod[pred[i].num]:=pred[j].num;
  for i:=0 to n do
    write(rod[i],' ');
end.