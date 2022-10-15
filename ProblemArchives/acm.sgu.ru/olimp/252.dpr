var a,b,i,k:integer;
function sumcif(a:integer):integer;
var b:integer;
begin
b:=0;
while a>0 do
begin
b:=b+a mod 10;
a:=a div 10;
end;
sumcif:=b;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a,b);
k:=0;
for i:=a to b do
if i mod sumcif(i)=0 then inc(k);
write(k);
end.