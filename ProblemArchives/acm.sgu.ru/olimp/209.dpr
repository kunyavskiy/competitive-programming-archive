var a,b:array[1..1000] of integer;
n,i,j:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
for i:=1 to n do
read(a[i]);
for i:=1 to 1000 do b[i]:=0;
for i:=1 to n do
inc(b[a[i]]);
i:=1;
while i<1000 do
begin
for j:=1 to b[i] do
write(i,' ');
i:=i+2;
end;
i:=1000;
while i>1 do
begin
for j:=1 to b[i] do write(i,' ');
i:=i-2;
end;
end.