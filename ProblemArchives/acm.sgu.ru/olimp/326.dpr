var A,x,y,n:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(A);
read(x);
read(y);
if (x>a) or (y>a) or (x<0) or (y<0) then write('2')
else if (x<a) and (y<a) and (x>0) and (y>0) then write('0')
 else write('1');
end.