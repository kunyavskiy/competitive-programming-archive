{$APPTYPE CONSOLE}

uses
  SysUtils;
var k,f,l,s,ko,p:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k,f,l,ko,s,p);
  write(1-k,' ',1-f,' ',2-l,' ',2-ko,' ',2-s,' ',8-p);
end.