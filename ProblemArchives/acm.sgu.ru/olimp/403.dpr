var a1,a2,a3,s:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a1);
read(a2);
read(a3);
s:=100*a1+10*a2+a3;
case s of
123:write('1 2 3');
132:write('1 3 2');
213:write('2 1 3');
231:write('3 1 2');
312:write('2 3 1');
321:write('3 2 1');
end;
end.