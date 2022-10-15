{$H+}
type int=longint;
var s: string;
n,i:int;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 while not eof do
 begin
  readln(s);
  n:=0;
  for i:=1 to length(s) do
  if s[i]='!'then n:=n+1;
  writeln(n);
  end;
end.
