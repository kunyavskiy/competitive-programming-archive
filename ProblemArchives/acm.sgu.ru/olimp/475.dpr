{$APPTYPE CONSOLE}
{$O+}

var a1,a,b,max,maxnum,n,i:integer;

function rasn:integer;
var a,b,c,d:integer;
begin
  read(a,b,c,d);
  result:=(b-d)*20+(a-c);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  a:=rasn;
  a1:=a;
  b:=rasn;
  max:=a+b;
  maxnum:=2;
  for i:=3 to n do
    begin
      a:=b;
      b:=rasn;
      if max<a+b then
        begin
          max:=a+b;
          maxnum:=i;
        end;
    end;
  a:=b;
  b:=a1;
  if max<a+b then write('1 ',n)
  else write(maxnum,' ',maxnum-1);
end.