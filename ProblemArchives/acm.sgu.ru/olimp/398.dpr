{$APPTYPE CONSOLE}
  var p,i:integer;
      a: array[0..100] of integer;
procedure sled (var q:integer);
begin
q:=sqr(q);
q:=q mod 1000;
q:=q div 10;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(p);
  i:=1;
  while a[p]=0 do
    begin
    a[p]:=i;
    sled(p);
    inc(i);
    end;
write(a[p]-1);
end.