program Project2;

{$APPTYPE CONSOLE}

uses
  SysUtils;
var x1,x2,x3,y1,y2,y3:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(x1,y1,x2,y2,x3,y3);
  if x1=x2 then
    if y1=y3 then write(x3,' ',y2)
    else write(x3,' ',y1)
  else if x1=x3 then write(x2,' ',y3)
      else write(x1,' ',y3);
end.