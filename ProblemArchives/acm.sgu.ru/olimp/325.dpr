{$APPTYPE CONSOLE}



uses
  Math;

type abcd=record
          v,kol:integer;
          end;
var  t:array[0..100,0..100] of abcd;
     v1,v2:abcd;
     n,i,l,j:integer;
     a:array[1..100] of integer;

function max(a,b:abcd):abcd;
begin
   if a.v>b.v then result:=a;
   if a.v<b.v then result:=b;
   if a.v=b.v then
      if a.kol<b.kol then result:=a
      else result:=b;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,l);
  for i:=1 to n do
    read(a[i]);
  for i:=0 to n do
    begin
      t[i,0].v:=0;
      t[i,0].kol:=0;
      t[0,i].v:=0;
      t[0,i].kol:=0;
    end;
  for i:=1 to n do
    for j:=1 to l do
      begin
        v1:=t[i,j-1];
        v2:=t[i-1,j];
        t[i,j]:=max(v1,v2);
        if j>=a[i] then
         begin
           v1.v:=t[i-1,j-a[i]].v+a[i];
           v1.kol:=t[i-1,j-a[i]].kol+1;
           t[i,j]:=max(t[i,j],v1);
         end;
      end;
  writeln(t[n,l].v);
  writeln(t[n,l].kol);
end.