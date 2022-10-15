var a1,b1,k:longint;
		a,b:real;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(a);
readln(b);
if a>b then write(0)
else
begin
a1:=trunc(a);
if a1<a then a1:=a1+1;
b1:=trunc(b);
if b1>b then b1:=b1-1;
write(b1-a1+1);
end;
end.
