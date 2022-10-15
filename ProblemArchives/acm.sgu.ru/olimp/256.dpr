{$APPTYPE CONSOLE}
{$r+,q+}

uses
  SysUtils;

var t:array[-200..200,1..10] of int64;
    n,p,i,j,k:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,p);
  dec(p);
  for i:=0 to p do
     t[i,1]:=1;
  for i:=2 to n do
    for j:=-100 to 100 do
    begin
      t[j,i]:=t[j,i-1];
      for k:=1 to p do
      t[j,i]:=t[j,i]+t[j-k,i-1]+t[j+k,i-1];
    end;
  write(t[0,n]);

end.