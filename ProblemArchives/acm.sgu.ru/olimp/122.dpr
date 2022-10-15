var M,N:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(N);
read(M);
if M mod N=0 then write('Party is coming')
else write('It is a boring day');
end.