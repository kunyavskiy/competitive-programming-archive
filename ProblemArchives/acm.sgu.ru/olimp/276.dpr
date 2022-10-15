{$APPTYPE CONSOLE}

uses
  SysUtils;
const koefv=3.2878976200991965732950122134715;
var r:real;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(r);
write(koefv*r:0:5);
end.