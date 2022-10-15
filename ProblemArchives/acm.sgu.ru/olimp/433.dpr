{$APPTYPE CONSOLE}

uses
  SysUtils,Math;

var s1,s2:string;
    a,b:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s1);
  readln(s2);
  if s2='INF' then
    begin
      s2:=s1;
      s1:='INF';
    end;
  if s1='INF' then
    begin
      if s2='1' then write('INF') else
      if s2='2' then write(4) else
        write(1);
      close(input);
      close(output);
      halt;
    end;
  a:=strtoint(s1);
  b:=strtoint(s2);
  if a>b then
    begin
      a:=a+b;
      b:=a-b;
      a:=a-b;
    end;
  if a=1 then
    write(b);
  if a=2 then
    write(min(4,2*b));
  if (a=3) and (b=3) then
    write(2);
  if ((a=3) and (b<>3)) or (a>3) then
    write(1);
end.