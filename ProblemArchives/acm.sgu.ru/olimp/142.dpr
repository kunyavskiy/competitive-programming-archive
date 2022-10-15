var m,a1,a2,b1,b2,a3,b3,i:longint;
function min(a,b:longint):longint;
begin
if a<b then min:=a else min:=b;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a1,b1);
read(a2,b2);
a3:=a1*b2+b1*a2;
b3:=b1*b2;
m:=min(a3,b3);
if a3=0 then b3:=1;
for i:=2 to m do
while (a3 mod i=0) and ( b3 mod i=0) do
begin
a3:=a3 div i;
b3:=b3 div i;
end;
write(a3,' ',b3);
end.