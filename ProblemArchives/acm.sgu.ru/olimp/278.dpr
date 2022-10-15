var a,b,ab,ba,i:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a);
read(b);
ab:=1;
ba:=1;
for i:=1 to b do
ab:=ab*a;
for i:=1 to a do
ba:=ba*b;
if ab=ba then write('EQUAL');
if ab>ba then write('GREATER');
if ab<ba then write('LESS');
end.