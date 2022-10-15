{$APPTYPE CONSOLE}
{$o+}
uses
  SysUtils;

var a,b,c,d:array[1..500] of integer;
    t,n,i:integer;

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
      t := c[i]; c[i] := c[j]; c[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;

procedure del(s1,s2,i:integer);
var j,t1,t2:integer;
begin
  if (s1>t) or (s2>t) then exit;
  if i=n+1 then
    begin
      t1:=0;
      t2:=0;
      for j:=1 to n do
        if b[j]=1 then
          begin
            d[c[j]]:=t1;
            t1:=t1+a[j];
          end
        else
          begin
            d[c[j]]:=t2;
            t2:=t2+a[j];
          end;
        for j:=1 to n do
          write(d[j],' ');
        close(input);
        close(output);
        halt;
    end;
  b[i]:=1;
  del(s1+a[i],s2,i+1);
  b[i]:=2;
  del(s1,s2+a[i],i+1);
end;




begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(t,n);
  for i:=1 to n do
    read(a[i]);
  for i:=1 to n do
    c[i]:=i;
  qsort(1,n);
  del(0,0,1);
end.