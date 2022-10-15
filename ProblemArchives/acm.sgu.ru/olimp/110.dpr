var a: integer;
    c:longint;
    i,n: longint;
begin
  assign(input,'input.txt');
  assign(output,'output.txt');
  reset(input);
  rewrite(output);
  read(n);
  c:=0;
  for i :=1 to n do
   begin
   read(a);
   c:=c+a;
   write(c/i:0:2,' ');
   end;
end.
 