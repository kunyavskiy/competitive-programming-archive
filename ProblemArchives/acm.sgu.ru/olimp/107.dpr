type int=longint;
			boy=record
			name:string[10];
			score:int;
			end;
var a : array [1..50] of boy;
		s,n,q,i,j:int;
		s1,s2:string[10];
		c:char;
procedure QSort(left, right : integer);
var m, i, j, t : integer;
		t1:string[10];
begin
	m := a[(left+right) div 2].score;
	i := left; j := right;
	repeat
		while a[i].score < m do inc(i);
		while a[j].score > m do dec(j);
		if i <= j then
		begin
			t := a[i].score; a[i].score := a[j].score; a[j].score := t;
			t1 := a[i].name; a[i].name := a[j].name; a[j].name := t1;
			inc(i); dec(j);
		end;
	until i > j;

	if j > left then QSort(left, j);
	if i < right then QSort(i, right);
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(n);
for i:=1 to n do readln(a[i].name);
for i:=1 to n do a[i].score:=0;
readln(q);
for i:=1 to q do
begin
s1:='';
s2:='';
read(c);
while not(c=' ') do
begin
s1:=s1+c;
read(c);
end;
read(c);
while not(c=' ') do
begin
s2:=s2+c;
read(c);
end;
readln(s);
j:=1;
while not (a[j].name=s1) do inc(j);
a[j].score:=a[j].score + s;
j:=1;
while not (a[j].name=s2) do inc(j);
a[j].score:=a[j].score - s;
end;
qsort(1,n);
for i:=1 to n do
begin
write(a[i].name,' ');
writeln(a[i].score);
end;
end.
