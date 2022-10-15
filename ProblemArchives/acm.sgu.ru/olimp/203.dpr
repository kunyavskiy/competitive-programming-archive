{$APPTYPE CONSOLE}

Uses
  Math;

type delitel=record
       del,step:int64;
       end;

var a:array[1..500000] of delitel;
    n:int64;
    k,i:integer;

procedure rasl;
var i:integer;
begin
  k:=0;
  i:=2;
  while i<=power(n,1/2) do
    begin
    if n mod i=0 then
      begin
        inc(k);
        a[k].del:=i;
        a[k].step:=0;
        while n mod i=0 do
          begin
            inc(a[k].step);
            n:=n div i;
          end;
      end;
    inc(i);
    end;
  if n<>1 then
    begin
      inc(k);
      a[k].del:=n;
      a[k].step:=1;
    end;
end;

function bol(a,b:delitel):boolean;
begin
  result:=a.step<b.step;
  result:=result or ((a.step=b.step) and (a.del>b.del));
end;

procedure qsort(l,r:integer);
var i,j:integer;
    t,m:delitel;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while bol(m,a[i]) do inc(i);
    while bol(a[j],m) do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
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
  rasl;
  qsort(1,k);
  writeln(k);
  for i:=1 to k do
    writeln(a[i].del,' ',a[i].step)
end.