{$APPTYPE CONSOLE}

var n,k,i,d,res:integer;
    a,b,c:array[1..1000] of boolean;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,k);
  for i:=1 to n do
     begin
     read(d);
     a[d]:=true;
     end;
  for i:=1 to n do
     begin
     read(d);
     b[d]:=true;
     end;
  for i:=1 to n do
     begin
     read(d);
     c[d]:=true;
     end;
  for i:=1 to 1000 do
    begin
      if a[i] and b[i] then b[i]:=false;
      if a[i] and c[i] then c[i]:=false;
    end;
  for i:=1 to 1000 do
    if (b[i] and c[i]) and (k>0) then
    begin
        b[i]:=false;
        c[i]:=false;
        dec(k);
        inc(res,2);
      end;
  for i:=1 to 1000 do
    if (b[i] or c[i]) and (k>0) then
      begin
        b[i]:=false;
        c[i]:=false;
        dec(k);
        inc(res,1);
      end;
  write(res);
end.
