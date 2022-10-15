{$APPTYPE CONSOLE}
{$I-;O+;R-;Q-}
uses
  SysUtils;
var c:char;
    s:string;
    i:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
while not eof do
begin
  read(c);
  while (c='P') and not(eof) do read(c);
  if not(eof) and (c='C') then
  begin
    read(c);
    if c='C' then
    s:=s+'2'
    else s:=s+'1';
  end
  else if c='c' then s[i]:='1';
end;
writeln(length(s));
for i:=1 to length(s)-1 do
write(s[i],' ');
write(s[length(s)]);
end.