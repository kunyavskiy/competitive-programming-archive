var ho,m,s:array[0..2] of integer;
p:char;
j:integer;
procedure schit(i:integer;var h:array of integer);
begin
read(p);
case p of
'1':h[i]:=10;
'2':h[i]:=20;
'3':h[i]:=30;
'4':h[i]:=40;
'5':h[i]:=50;
'6':h[i]:=60;
end;
read(p);
case p of
'1':h[i]:=h[i]+1;
'2':h[i]:=h[i]+2;
'3':h[i]:=h[i]+3;
'4':h[i]:=h[i]+4;
'5':h[i]:=h[i]+5;
'6':h[i]:=h[i]+6 ;
'7':h[i]:=h[i]+7;
'8':h[i]:=h[i]+8;
'9':h[i]:=h[i]+9;
end;
end ;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
ho[1]:=0;
ho[2]:=0;
m[1]:=0;
m[2]:=0;
s[1]:=0;
s[2]:=0;
for j:=0 to 1 do
begin
schit(j,ho);
read(p);
schit(j,m);
read(p);
schit(j,s);
readln;
end;
ho[2]:=ho[0]+ho[1];
m[2]:=m[0]+m[1];
s[2]:=s[0]+s[1];
if s[2]>=60 then
begin
s[2]:=s[2]-60;
m[2]:=m[2]+1;
end;
if m[2]>=60 then
begin
m[2]:=m[2]-60;
ho[2]:=ho[2]+1;
end;
if ho[2]>=24 then
ho[2]:=ho[2]-24;
if ho[2]>=10 then write(ho[2],':')
else write('0',ho[2],':');
if m[2]>=10 then write(m[2],':')
else write('0',m[2],':');
if s[2]>=10 then write(s[2])
else write('0',s[2]);
end.