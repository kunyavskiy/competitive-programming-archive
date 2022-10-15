var a,b,c,d:real;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
read(b);
c:=(a+b)/2;
d:=sqrt(a*b);
write(sqrt(c*d):0:2);
end.