var l:array [1..4] of integer;
n,k,i:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(l[1]);
read(l[2]);
read(l[3]);
read(l[4]);
k:=0;
for i:=2 to 4 do
if l[1]=l[i] then
begin
n:=n+1;
k:=i;
break;
end;
case k of
2:if l[3]=l[4] then n:=n+1;
3:if l[2]=l[4] then n:=n+1;
4:if l[2]=l[3] then n:=n+1;
0:if (l[3]=l[4]) or (l[2]=l[3]) or(l[2]=l[4]) then n:=n+1;
end;
write(n)
end.