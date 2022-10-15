var ax,bx:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(ax);
read(bx);
if ax>bx then write(ax-1)
else write(ax+1);
end.