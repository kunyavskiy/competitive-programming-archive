{$APPTYPE CONSOLE}
uses
  SysUtils;
var x,y,k:integer;
procedure swap (var a,b:integer);
var t:integer;
begin
t:=a;
a:=b;
b:=t;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(x,y)                    ;
k:=0;
if (x=y) and (not (x=1)) then k:=-1
else
while not((x=y) and (x=1)) do
  begin
  if x<y then swap(x,y);
  if y=1 then
    begin
    k:=k+x-1;
    break;
    end;
  if x mod y =0 then
    begin
    k:=-1;
    break;
    end
  else
    begin
    k:=k+ (x div y);
    x:=x mod y;
    end;
  end;
write(k);
end.