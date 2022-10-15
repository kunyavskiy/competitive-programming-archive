var a,b,i:integer;
		c,c1:char;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
a:=0;
for i:=1 to 3 do
begin
	read(c);
	case c of
	'1':a:=a*10+1;
	'2':a:=a*10+2;
	'3':a:=a*10+3;
	'4':a:=a*10+4;
	'5':a:=a*10+5;
	'6':a:=a*10+6;
	'7':a:=a*10+7;
	'8':a:=a*10+8;
	'9':a:=a*10+9;
	'0':a:=a*10;
	'-','+','*','/':break;
	end;
end;
	b:=0;
if not((c='+') or (c='-') or (c='*') or (c='/')) then read(c);
for i:=1 to 3 do
begin
	read(c1);
	case c1 of
	'1':b:=b*10+1;
	'2':b:=b*10+2;
	'3':b:=b*10+3;
	'4':b:=b*10+4;
	'5':b:=b*10+5;
	'6':b:=b*10+6;
	'7':b:=b*10+7;
	'8':b:=b*10+8;
	'9':b:=b*10+9;
	'0':b:=b*10;
	'=':break;
	end;
end;
case c of
	'-':write(a-b);
	'+':write(a+b);
	'*':write(a*b);
	'/':write(a div b);
	end;
end.
