var x1,x2,x3,x4,y1,y2,y3,y4,r12,r13,r14,r23,r24,r34:real;
		i,m:integer;
		q:boolean;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(m);
for i:=1 to m do
begin
readln(x1,y1);
readln(x2,y2);
readln(x3,y3);
readln(x4,y4);
x1:=x1/1000000;
x2:=x2/1000000;
x3:=x3/1000000;
x4:=x4/1000000;
y1:=y1/1000000;
y2:=y2/1000000;
y3:=y3/1000000;
y4:=y4/1000000 ;
r12:=sqrt(sqr(x1-x2)+sqr(y1-y2));
r13:=sqrt(sqr(x1-x3)+sqr(y1-y3));
r14:=sqrt(sqr(x1-x4)+sqr(y1-y4));
r23:=sqrt(sqr(x3-x2)+sqr(y3-y2));
r24:=sqrt(sqr(x4-x2)+sqr(y4-y2));
r34:=sqrt(sqr(x3-x4)+sqr(y3-y4));
q:=(r12=r23) and (r23=r34) and (r34=r14) and(r13=r24);
q:=((r13=r23) and (r23=r24) and (r24=r14) and(r12=r34)) or q;
q:=((r12=r24) and (r24=r34) and (r34=r13) and(r14=r23)) or q;
if q then writeln('YES')
else writeln('NO');
end;
end.





end.