{$APPTYPE CONSOLE}
uses
  SysUtils;
type aray=array[1..50] of integer;
var n,i,j:integer;
    a:aray;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  i:=50;
  fillchar(a,sizeof(a),0);
  if n mod 2 =0 then write('No solution')
    else
    begin
    while n>1 do
    begin
      if ((n+1) div 2) mod 2 =1 then
        begin
        a[i]:=1;
        n:=(n+1) div 2;
        end
      else
        begin
        a[i]:=2;
        n:=(n-1) div 2;
        end;
      dec(i);
    end;
    writeln(50-i);
    for j:=i+1  to 50 do write(a[j],' ');
   end
end.