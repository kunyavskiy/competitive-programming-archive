{$APPTYPE CONSOLE}

uses
  SysUtils;

var n,x,a,i:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,x);
  for i:=1 to n do
     begin
       read(a);
       x:=x-a;
       if x<0 then
         begin
           write(i-1);
           exit;
         end;
     end;
  write(n);
end.