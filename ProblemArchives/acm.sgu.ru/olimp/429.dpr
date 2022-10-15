{$APPTYPE CONSOLE}

var a:array[1..100000] of record
                          x,y:integer;
                          end;
    xs,ys:array[1..100000] of int64;
    r:int64;
    n,i:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
      read(a[i].x);
      read(a[i].y);
      inc(xs[a[i].x]);
      inc(ys[a[i].y]);
    end;
  r:=0;
  for i:=1 to n do
    r:=r+(xs[a[i].x]-1)*(ys[a[i].y]-1);
  write(r);
end.