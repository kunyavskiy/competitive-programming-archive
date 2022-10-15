{$APPTYPE CONSOLE}

uses math;

type abcd=record
         p,d:int64;
         end;

var a:array[1..100] of abcd;
    tp,tm:int64;
    i,j,n:integer;

procedure swap(var a,b:abcd);
var t:abcd;
begin
   t:=a;
   a:=b;
   b:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(a[i].p);
  for i:=1 to n do
    read(a[i].d);
  for i:=1 to n do
    for j:=i+1 to n do
      if a[i].d<a[j].d then swap(a[i],a[j]);
  tp:=0;
  tm:=0;
  for i:=1 to n do
     begin
       tp:=tp+a[i].p;
       tm:=max(tm,tp+a[i].d);
     end;
  write(tm);
end.