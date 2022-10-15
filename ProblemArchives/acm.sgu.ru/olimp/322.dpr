{$APPTYPE CONSOLE}
var k,v,o,m,f,s,t: integer;
tp:real;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(k);
read(v);
read(o);
read(m);
read(f);
read(s);
read(t);
tp:=(K/v+O*(M/60))*2+f+s+t+1;
write(tp:0:3);
end.
