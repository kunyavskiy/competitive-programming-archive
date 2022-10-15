{$APPTYPE CONSOLE}
uses
  SysUtils;
var c:string;
    k,i,j,l,kt:integer;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 readln(k);
 readln(c);
 kt:=k;
 for i:=1 to k do
  begin
  dec(kt);
  for j:=1 to length(c) do
    begin
      for l:=1 to k-kt do write(c[j]);
      for l:=1 to kt do write('~');
    end;
  writeln
  end;
end.