var x11,x12,x21,x22,i,n:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read (n);
for i:=1 to n do
begin
read(x11);
read(x12);
read(x21);
read(x22);
if ((x12>=x21) and (x11<=x21)) or ((x12>=x22) and(x11<=x22)) or ((x12<=x22) and(x11>=x21)) then writeln('YES')
else writeln('NO');
end
end.