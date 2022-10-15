var n,i,j,num:integer;
		a:array[1..14]  of integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
i:=0;
while n>=2 do
begin
a[14-i]:=n mod 2;
n:=n div 2;
i:=i+1     ;
end;
if not(n=0) then
begin
write ('1');
for j:=14-i+1 to 14 do  write(a[j]);
end
else write('0')
end.