{$APPTYPE CONSOLE}
uses
  math;
var x1,x2,y1,y2,t:longint;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 read(x1,y1,x2,y2);
 t:=max(abs(x1-x2),abs(y1-y2));
 write(t);
end.