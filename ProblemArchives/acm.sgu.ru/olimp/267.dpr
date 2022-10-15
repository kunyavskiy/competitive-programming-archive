var N,P:INTEGER;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(N);
read(P);
if P mod N =0 then
write(N)
else write(P mod N )
end.