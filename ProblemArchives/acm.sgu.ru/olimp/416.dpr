var v,ni,s:array[1..10000] of longint;
		i,n,max1,max2,num:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read (n);
for i:=1 to n do
begin
read(v[i]);
read(ni[i]);
end;
for i:=1 to n do
s[i]:=v[i]*3+ni[i];
max1:=s[1];
num:=1;
for i:=1 to n do
if s[i]>=max1 then
begin
num:=i;
max1:=s[i];
end;
s[num]:=-1;
max2:=s[1];
num:=1;
for i:=1 to n do
if s[i]>=max2 then
max2:=s[i];
write(max1-max2);

end.