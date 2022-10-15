var x1,x2,y1,y2,r1,r2:longint;
		d:real;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(x1,y1,r1);
read(x2,y2,r2);
d:=sqrt(sqr(x1-x2)+sqr(y1-y2));
if (d=0)  then
	if r1=r2 then
		if r1=0 then write(1)
		else write(-1)
	else write(0)
else
		if (d<r1+r2) and (d>abs(r1-r2)) then write(2)
		else if (d=r1+r2) or (d=abs(r1-r2)) then write(1)
				else write(0);
end.
