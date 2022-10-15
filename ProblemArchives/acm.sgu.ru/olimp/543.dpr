{$APPTYPE CONSOLE}

uses
  SysUtils;

var n,i,j,k:integer;
    s:string;

function good(x,y:integer):char;
begin
  if x=1 then
    begin
      if (y=n) or (y<=(n div 2)+(n mod 2)) then
         result:='*'
      else
        result:='.';
      exit
    end;
   if x=n then
    begin
      if (y=1) or (y>(n div 2)+(n mod 2)) then
         result:='*'
      else
        result:='.';
      exit
    end;
   if y=1 then
    begin
      if (x=1) or ((x>(n div 2)) and (n mod 2=0)) or ((x>=(n div 2)+1) and (n mod 2=1)) then
         result:='*'
      else
        result:='.';
      exit
    end;
    if y=n then
    begin
      if (x=n) or (x<=(n div 2)+(n mod 2)) then
         result:='*'
      else
        result:='.';
      exit
    end;
   result:='.';


end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
      for j:=1 to n do
        write(good(i,j));
      writeln;
    end;


end.
