var a,b,c,k:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
read(b);
read(c);
write(abs(a-b)+abs(b-c));
end.