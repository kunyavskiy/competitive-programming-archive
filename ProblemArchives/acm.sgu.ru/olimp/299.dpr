{$APPTYPE CONSOLE}
uses
  SysUtils;
var i,n,x1,x2,y1,y2:integer;
    yes:boolean;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
for i:=1 to n do
begin
readln(x1,y1,x2,y2);
yes:=false;
if (x1=x2) and (y1+y2=x1) then  yes:=true
  else if(x1=y2) and (y1+x2=x1) then yes:=true
     else if (y1=x2) and (x1+y2=x2) then yes:=true
      else if (y1=y2) and (x1+x2=y1) then yes:=true;
if yes=true then writeln('YES')
else writeln('NO');
end;
end.