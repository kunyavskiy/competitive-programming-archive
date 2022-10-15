program tr01;

{$APPTYPE CONSOLE}

uses
  Math;

var v11,v12,v13,v1,v2,l1,l2,l3,x:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(l1,l2,l3,x);
  v11:=l1*x;
  v12:=l2*min(x,l2);
  v13:=l3*min(x,l3);
  v1:=v11+v12+v13;
  v2:=l1*l1+l2*l2+l3*l3-v1;
  write(v1,' ',v2);
end.
