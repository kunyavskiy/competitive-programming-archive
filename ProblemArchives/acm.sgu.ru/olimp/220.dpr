{$APPTYPE CONSOLE}
{$H+,r-,q-,o-}

var s:string;
    i:integer;

procedure makesmall(var c:char);
begin
  if (c in ['.',',',' ','a'..'z']) or (ord(c)=13) or (ord(c)=10) then exit;;
  c:=chr(ord(c)-ord('A')+ord('a'));
end;

procedure makebig(var c:char);
begin
  if (c in ['.',',',' ','A'..'Z']) or (ord(c)=13) or (ord(c)=10) then exit;;
  c:=chr(ord(c)+ord('A')-ord('a'));
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  if eof then
    begin
     close(input);
     close(output);
     halt;
    end;
  readln(s);
  i:=1;
  while i<length(s) do
  begin
    if s[i] in ['.',','] then
     begin
     insert(' ',s,i+1);
     inc(i);
     end;
    inc(i);
  end;
  i:=1;
  while i<=length(s) do
  begin
    while ((i=1) and (s[i]=' ')) or ((i>1) and (s[i-1]=' ') and (s[i]=' ')) do
     begin
      delete(s,i,1);
      if i>length(s) then break;
     end;
    inc(i);
  end;
  if s<>'' then
  begin
  i:=length(s);
  while s[i]=' ' do
    begin
      delete(s,i,1);
      dec(i);
    end;
  end;
  i:=1;
  while i<length(s) do
  begin
    while (s[i]=' ') and (s[i+1] in ['.',',']) do
      delete(s,i,1);
    inc(i);
  end;
  i:=1;
  while i<=length(s) do
  begin
    if (i=1) then makebig(s[i]);
    if (i>=3) and (s[i-2]='.') then makebig(s[i]);
    inc(i);
  end;
  i:=1;
  while i<=length(s) do
  begin
    if (i=2)  or ((i>=3) and (s[i-2]<>'.')) then makesmall(s[i]);
    inc(i);
  end;
  write(s);
end.