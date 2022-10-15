var st:string;
i,n:integer;
k,m,s:real;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
readln(k);
k:=k/100;
for i:=1 to n do
begin
readln(st);
if st[1]='S' then s:=s+length(st)*k
else m:=m+length(st)*k;
end;
write(s:0:2,' ',m:0:2);
end.