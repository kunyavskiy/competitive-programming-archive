{$APPTYPE CONSOLE}

uses
  SysUtils;
 var x1,x2,x3,x4,y1,y2,y3,y4,d12,d13,d14,d23,d24,d34:int64;
     i,m:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(m);
  for i:=1 to m do
  begin
   read(x1,y1);
   read(x2,y2);
   read(x3,y3);
   read(x4,y4);
   d12:=sqr(x1-x2)+sqr(y1-y2);
   d13:=sqr(x1-x3)+sqr(y1-y3);
   d14:=sqr(x1-x4)+sqr(y1-y4);
   d23:=sqr(x2-x3)+sqr(y2-y3);
   d24:=sqr(x2-x4)+sqr(y2-y4);
   d34:=sqr(x3-x4)+sqr(y3-y4);
   if (d12=d23) and (d12=d34) and (d12=d14) and (d13=d24) then writeln('YES')
   else if (d13=d23) and (d13=d24) and (d13=d14) and (d12=d34) then writeln('YES')
   else if (d13=d34) and (d13=d24) and (d13=d12) and (d14=d23) then writeln('YES')
   else writeln('NO')
  end;
end.