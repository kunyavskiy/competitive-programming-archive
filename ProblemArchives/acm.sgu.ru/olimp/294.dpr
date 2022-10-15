{$APPTYPE CONSOLE}
uses
  SysUtils;
var s:integer;
procedure skob (var a:integer);
var c,z:char;
    b:integer;
begin
a:=0;
z:='+';
while not eof do
begin
read(c);
if c in ['1'..'9'] then
if z='+' then a:=a+strtoint(c)
else a:=a-strtoint(c);
if c='+' then z:='+';
if c='-' then z:='-';
if c='(' then
begin
skob(b);
if z='+' then a:=a+b
else a:=a-b;
end;
if c=')' then break;
end;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
skob(s);
write(s);
end.