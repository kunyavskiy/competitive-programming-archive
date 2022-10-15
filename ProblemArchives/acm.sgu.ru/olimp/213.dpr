var n,k:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
k:=0;
while n>0 do
begin
if n mod 2 =1 then k:=k+1;
n:=n div 2;
end;
write(k);
end.
