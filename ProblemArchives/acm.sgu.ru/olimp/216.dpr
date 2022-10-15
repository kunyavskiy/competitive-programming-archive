var a1,a2,a3,n:INTEGER;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a1);
read(a2);
read(a3);
if a1=a2 then
 if a1=a3  then write('1')
 else write('2')
else if (a1=a3) or (a2=a3) then
write('2')
else write('3')
end.