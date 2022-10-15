{$APPTYPE CONSOLE}
uses
  SysUtils,math;
var a,b,c,d,r1,r2:real;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(a,b,c);
if a<0 then
begin
a:=-a;
b:=-b;
c:=-c;
end;
if a=0 then
  if b=0 then
    if c=0 then write('INFINITE')
    else write(0)
  else if c=0 then
        begin
          writeln(1);
          r1:=0;
          write(r1:0:5);
        end
        else
        begin
        writeln(1);
        write(-1*c/b:0:5);
        end
else
  if b=0 then
    if c=0 then
    begin
    writeln(1);
    r1:=0;
    write(R1:0:5);
    end
    else if c>0 then write(0)
          else
          begin
          writeln(2);
          writeln(sqrt(-1*c/a):0:5);
          writeln(-1*sqrt(-1*c/a):0:5);
          end
  else if c=0 then
        begin
        writeln(2);
        writeln(min(0,-1*b/a):0:5);
        write(max(0,-1*b/a):0:5);
        end
        else
        begin
        a:=a/10000;
        b:=b/10000;
        c:=c/10000;
        d:=sqr(b)-4*a*c;
        if d>0 then
        begin
        writeln(2);
        r1:=(-b+sqrt(d))/(2*a);
        r2:=(-b-sqrt(d))/(2*a) ;
        writeln(min(r1,r2):0:5);
        writeln(max(r1,r2):0:5);
        end
        else if d<0 then write(0)
              else
              begin
              writeln(1);
              write(-b/(2*a):0:5);
              end;
        end;
end.