var a,b,n,k,i:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
k:=0;
for i:=1 to n do
begin
read(a);
read(b);
if a mod 2 = b mod 2 then k:=k+1;
end;
write(k);
end.