var n,k,i:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
k:=0;
if n=0 then write(-1)
else
begin
n:=abs(n);
for i:=1 to trunc(sqrt(n)) do
if n mod i =0 then inc(k);
k:=k*2;
if sqrt(n)=trunc(sqrt(n)) then dec(k);
k:=k*2;
write(k);
end;
end.