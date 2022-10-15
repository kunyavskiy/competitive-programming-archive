var a:array[1..1001] of longint;
		b:array[1..144] of longint;
		n,i,p,d,s,g:longint;
function min(a,b:longint):longint;
begin
if a<b then min:=a
else min:=b;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
fillchar(a,sizeof(a),0);
for i:=1 to n do
begin
read(p);
readln(a[p]);
end;
for i:=1 to 1001 do
if i mod 7=0 then b[(i div 7)]:=b[(i div 7)]+a[i]
else b[(i div 7)+1]:=b[(i div 7)+1]+a[i];
for i:=1 to 1001 do s:=s+a[i];
d:=1;
for i:=1 to 143 do
begin
g:=min(10000,b[i]);
s:=s-g;
b[i]:=b[i]-g;
b[i+1]:=b[i+1]+b[i];
b[i]:=0;
d:=d+7;
if s=0 then break;
end;
d:=d+(s div 10000)*7;
s:=s mod 10000;
if s<>0 then d:=d+7;
write(d);
end.