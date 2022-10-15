{$APPTYPE CONSOLE}
uses
  SysUtils;
var s:string;
    c1:char;
procedure de (var sv:string);
var c:char;
    s1,b:string;
    j:integer;
begin
while true do
begin
read(c);
case c of
'1','2','3','4','5','6','7','8','9','0':b:=b+c;
')':break;
'(':de(s1);
else s1:=s1+c;
end;
end;
for j:=1 to strtoint(b) do sv:=sv+s1;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
while not eof do
begin
read(c1);
if c1='(' then de(s)
else s:=s+c1;
end                 ;
write(s);
end.