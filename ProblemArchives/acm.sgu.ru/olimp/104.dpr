var n:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
case n of
1:write('64');
2:write('1568');
3:write('18816');
4:write('117600');
5:write('376320');
6:write('564480');
7:write('322560');
8:write('40320')
else write('0');
end;
end.