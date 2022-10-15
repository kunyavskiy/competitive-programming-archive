{$APPTYPE CONSOLE}
uses
  SysUtils;
var n,c,i:integer;
    a,b:array[-1000..1000] of boolean;
    ch:array[1..2000] of integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
begin
read(c);
a[c]:=true;
end;
read(n);
for i:=1 to n do
begin
read(c);
b[c]:=true;
end;
c:=0;
for i:=-1000 to 1000 do
if (a[i]=true) xor (b[i]=true) then
begin
inc(c);
ch[c]:=i;
end;
write(c,' ');
for i:=1 to c do
write(ch[i],' ');
end.