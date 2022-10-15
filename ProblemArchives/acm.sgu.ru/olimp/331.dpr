{$APPTYPE CONSOLE}
{$O+}

uses
  Math;



var f:array[1..60] of int64;
    i,q,n,m:integer;

procedure print(a,b:integer);
begin
  if a=1 then
   begin
     writeln('A');
     exit;
   end;
  if a=2 then
    begin
      if b=1 then writeln('A');
      if b=2 then writeln('B');
      exit;
    end;
 if b>f[a-2] then print(a-1,b-f[a-2])
 else print(a-2,b);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  f[1]:=1;
  f[2]:=2;
  for i:=3 to 60 do
     f[i]:=f[i-1]+f[i-2];
  read(q);
  for i:=1 to q do
    begin
      read(m,n);
      if m>f[n] then
         begin
           writeln('No solution');
           continue;
         end;
      print(n,m);
    end;
end.