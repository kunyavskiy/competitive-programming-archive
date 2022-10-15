var max,n,i,b:integer;
		sti:string[5];
	procedure perevod (st:string; var c:integer) ;
	var ras,j,a:integer;
	begin
	j:=1;
	while not ((st[j]='s') or (st[j]='m')) do
	 j:=j+1;
	ras:=j-1;
	if st[ras+1]='s' then
	begin
		st[ras+1]:='0';
		ras:=ras+1
	end
	else st[ras+1]:=' ';
	a:=1;
	c:=0;
	for j:=1 to ras do
	begin
	case st[ras+1-j] of
	'1':c:=c+a;
	'2':c:=c+2*a;
	'3':c:=c+3*a;
	'4':c:=c+4*a;
	'5':c:=c+5*a;
	'6':c:=c+6*a;
	'7':c:=c+7*a;
	'8':c:=c+8*a;
	'9':c:=c+9*a;
	end;
	a:=a*10;
	end;
	end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(n);
max:=0;
for i:=1 to n do
begin
readln(sti);
perevod(sti,b);
if b>max then max:=b;
end;
write(max);
end.