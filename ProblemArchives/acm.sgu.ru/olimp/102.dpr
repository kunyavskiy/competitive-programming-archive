type  int=integer;
			cl=record
			buk:int;
			cif:int;
			end;
var g:array[-1..10,-1..10] of boolean;
		o:array[1..65] of cl;
		p:array[-1..10,-1..10] of cl;
		a,b,h,t,i:int;
		st,e,v:cl;
		c:char;
function chartoint(c:char):int;
begin
case c of
'1','A':chartoint:=1;
'2','B':chartoint:=2;
'3','C':chartoint:=3;
'4','D':chartoint:=4;
'5','E':chartoint:=5;
'6','F':chartoint:=6;
'7','G':chartoint:=7;
'8','H':chartoint:=8;
end;
end;
function intochar(c:int):char;
begin
case c of
1:intochar:='A';
2:intochar:='B';
3:intochar:='C';
4:intochar:='D';
5:intochar:='E';
6:intochar:='F';
7:intochar:='G';
8:intochar:='H';
end;
end;
procedure go (v:cl);
begin
inc(h);
if (p[v.buk+2,v.cif+1].cif=0) and g[v.buk+2,v.cif+1] then
begin
inc(t);
o[t].buk:=v.buk+2;
o[t].cif:=v.cif+1;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk+2,v.cif-1].cif=0) and g[v.buk+2,v.cif-1] then
begin
inc(t);
o[t].buk:=v.buk+2;
o[t].cif:=v.cif-1;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk-2,v.cif+1].cif=0) and g[v.buk-2,v.cif+1] then
begin
inc(t);
o[t].buk:=v.buk-2;
o[t].cif:=v.cif+1;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk-2,v.cif-1].cif=0) and g[v.buk-2,v.cif-1] then
begin
inc(t);
o[t].buk:=v.buk-2;
o[t].cif:=v.cif-1;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk+1,v.cif+2].cif=0) and g[v.buk+1,v.cif+2] then
begin
inc(t);
o[t].buk:=v.buk+1;
o[t].cif:=v.cif+2;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk+1,v.cif-2].cif=0) and g[v.buk+1,v.cif-2] then
begin
inc(t);
o[t].buk:=v.buk+1;
o[t].cif:=v.cif-2;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk-1,v.cif+2].cif=0) and g[v.buk-1,v.cif+2] then
begin
inc(t);
o[t].buk:=v.buk-1;
o[t].cif:=v.cif+2;
p[o[t].buk,o[t].cif]:=v;
end;
if (p[v.buk-1,v.cif-2].cif=0) and g[v.buk-1,v.cif-2] then
begin
inc(t);
o[t].buk:=v.buk-1;
o[t].cif:=v.cif-2;
p[o[t].buk,o[t].cif]:=v;
end;
if not (o[h].cif=0) then go(o[h]);
end;
begin;
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(c);
st.buk:=chartoint(c);
readln(c);
st.cif:=chartoint(c);
read(c);
e.buk:=chartoint(c);
readln(c);
e.cif:=chartoint(c);
fillchar(g,sizeof(g),true);
for i:=-1 to 10 do
begin
g[0,i]:=false  ;
g[-1,i]:=false;
g[9,i]:=false;
g[10,i]:=false;
g[i,-1]:=false;
g[i,0]:=false;
g[i,9]:=false  ;
g[i,10]:=false;
end;
while not eof do
begin
read(c);
a:=chartoint(c);
read(c);
b:=chartoint(c);
g[a,b]:=false;
end;
h:=1;
t:=1;
o[1]:=e;
o[65].cif:=0;
o[65].buk:=0;
go(e);
if p[st.buk,st.cif].cif=0 then write('0')
else
begin
	v.cif:=st.cif;
	v.buk:=st.buk;
	while not((v.cif=e.cif) and (v.buk=e.buk)) do
	begin
		write(intochar(v.buk));
		write(v.cif);
		v:=p[v.buk,v.cif];
	end;
end;
write(intochar(e.buk));
write(v.cif);
end.
