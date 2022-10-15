var a:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
if a mod 3 =0 then write(a div 3 -1,' ',a div 3,' ', a div 3+1)
else write(-1)
end.