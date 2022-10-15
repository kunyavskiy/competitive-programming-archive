var k,i,n:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(k);
n:=0;
for i:=1 to k do
begin
n:=n+1;
while (n mod 2 =0) or (n mod 5=0) do n:=n+1;
end ;
write(n);
end.
