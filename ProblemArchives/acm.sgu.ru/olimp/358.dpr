var a:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
write(a div 10 - 9*(a div 100)+ a mod 10)
end.