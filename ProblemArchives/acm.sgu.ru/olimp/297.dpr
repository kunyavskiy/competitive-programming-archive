{$H+}

var s,s1:string;
    c,c1:char;
    i:integer;

procedure zapros(var a:string);
var i:integer;
begin
for i:=1 to length(s)-length(a)+1 do
  if copy(s,i,length(a))=a then
    begin
    writeln('YES');
    exit;
    end;
writeln('NO');
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not eof do
   begin
    read(c);
    read(c1);
    read(c1);
    if c1 in ['A'..'Z'] then
        c1:=chr(ord(c1)+ord('a')-ord('A'));
    s1:='';
    while (ord(c1)<>10) and (ord(c1)<>13) do
     begin
     s1:=s1+c1;
     read(c1);
     if c1 in ['A'..'Z'] then
        c1:=chr(ord(c1)+ord('a')-ord('A'));
     end;
    readln;
    if c='A' then s:=s+s1;
    if c='?' then zapros(s1);
   end;
end.