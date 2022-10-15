{$APPTYPE CONSOLE}

uses
   Math;

type product=record
           u,b,g:integer;
           end;

var a,b,x,y,i,j:integer;
    p1,p2:product;

function ok(k1,k2:integer):boolean;
var uo,bo,go,kal:integer;
begin
  uo:=k1*p1.u+k2*p2.u;
  bo:=k1*p1.b+k2*p2.b;
  go:=k1*p1.g+k2*p2.g;
  kal:=uo*4+bo*4+go*9;
  result:=kal<=b;
  result:=result and (kal>=a);
  result:=result and (go>=x);
  result:=result and (bo>=y);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,x,y);
  read(p1.g,p1.b,p1.u);
  read(p2.g,p2.b,p2.u);
  for i:=0 to 2000 do
    for j:=0 to 2000 do
      if ok(i,j) then
        begin
          write(i,' ',j);
          close(input);
          close(output);
          halt;
        end;
  write(-1);
end.