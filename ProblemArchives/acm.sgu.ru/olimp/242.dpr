
var t:array[0..31,0..31] of integer;
	s:array[0..31] of char;
	l,r,c:array[0..31] of integer;
	n,i:integer;

function calc(l,r:integer):integer;
var i,tmp:integer;
begin
	if (l>r) then
	begin
		Result:=0;
		exit;
	end;
	if (t[l,r]<>-1) then
	begin
		Result:=t[l,r];
		exit;
	end;
	while (l<r) and (s[r]=s[l]) do
		dec(r);
	if (l=r) then
	begin
		Result:=0;
		exit;
	end;
	t[l,r]:=127;
	for i:=l to r do
		if (s[i] = s[r]) then
		begin
			tmp:=calc(l,i-1)+calc(i,r)+1;
			if (t[l][r] > tmp) then
				t[l][r]:=tmp;
		end;
	Result:=t[l][r];
end;

procedure gen(lf,rg:integer);
var ans,i:integer;
begin
	if (lf>rg) then
		exit;
	ans:=calc(lf,rg);
	while (lf<rg) and (s[rg]=s[lf]) do
		dec(rg);
	if (lf=rg) then
		exit;
	for i:=lf to rg do
		if (s[i]=s[rg]) then
			if (ans = calc(lf,i-1)+calc(i,rg)+1) then
			begin
				l[l[0]]:=i;inc(l[0]);
				r[r[0]]:=rg;inc(r[0]);
				c[c[0]]:=ord(s[rg]);inc(c[0]);
				gen(lf,i-1);
				gen(i,rg);
				exit;
			end;
end;


begin
    reset(input,'input.txt');
    rewrite(output,'output.txt');
	fillchar(t,sizeof(t),-1);
	readln(n);
	for i:=0 to n-1 do
		read(s[i]);	
	writeln(calc(0,n-1)+1);
	l[0]:=1;
	r[0]:=1;
	c[0]:=1;
	l[l[0]]:=0;inc(l[0]);
	r[r[0]]:=n-1;inc(r[0]);
	c[c[0]]:=ord(s[0]);inc(c[0]);
	gen(0,n-1);
	for i:=1 to l[0]-1 do
		writeln(l[i]+1,' ',r[i]+1,' ',chr(c[i]));
end.
