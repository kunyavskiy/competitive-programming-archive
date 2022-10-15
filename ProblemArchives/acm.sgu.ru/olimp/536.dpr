{$APPTYPE CONSOLE}

uses
  Math;

var n,res,i,a,kol100,kol50:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  kol50:=0;
  kol100:=0;
  for i:=1 to n do
    begin
      read(a);
      if a=50 then
         inc(kol50)
    else
      inc(kol100);
    end;
  res:=kol100;
  kol50:=kol50-kol100;
  while kol50>0 do
    begin
      dec(kol50,3);
      inc(res);
    end;
  write(res);


end.