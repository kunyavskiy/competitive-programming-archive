var n,i:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
i:=1;
while sqr(i)<n do
begin
n:=n-sqr(i);
i:=i+1;
end;
write(i);
end.

