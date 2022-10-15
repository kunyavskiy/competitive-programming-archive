var a,b: array[1..3] of integer;
		maxa,maxb,num,i,j,s:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
for i:=1 to 3 do
read(a[i]);
for i:=1 to 3 do
read(b[i]);
s:=0;
for i:=1 to 3 do
 begin
 maxa:=a[1];
 num:=1;
 for j:=2 to 3 do
 if a[j]>maxa then
	begin
	maxa:=a[j];
	num:=j;
	end;
 a[num]:=0;
 num:=1;
 maxb:=b[1];
 for j:=2 to 3 do
 if b[j]>maxb then
	begin
	maxb:=b[j];
	num:=j;
	end;
 b[num]:=0;
 s:=s+maxa*maxb;
 end;
 write(s);
end.