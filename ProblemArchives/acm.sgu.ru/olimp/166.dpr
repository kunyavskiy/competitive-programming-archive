var m,n,i,j:integer;
		c:char;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
readln(m);
i:=1;
j:=1;
while not eof do
begin
read(c);
case c of
'L':j:=j-1;
'R':j:=j+1;
'D':i:=i+1;
'U':i:=i-1;
end;
if j=0 then j:=m;
if j=m+1 then j:=1;
if i=0 then i:=n;
if i=n+1 then i:=1;
if c='P' then writeln((i-1)*m+j);
end;
end.


