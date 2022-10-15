{$APPTYPE CONSOLE}
  var a,b,s,i:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a);
read(b);
s:=a;
for i:=2 to b do
begin
if i mod 5=0 then a:=a-2
else a:=a+1;
s:=s+a;
end;
write(s);
end.