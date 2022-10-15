var a:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
write(a div 240,' ');
a:=a-(a div 240)*240;
write(a div 12,' ') ;
a:=a-(a div 12)*12;
write(a);
end.