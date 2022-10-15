{$APPTYPE CONSOLE}
uses
  SysUtils;
var   l1,l2,m,n,j,i:integer;
      s:array[1..1000] of integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
  read(s[i]);
  m:=maxlongint;
  for i:=1 to n do
    for j:=i+1 to n do
  begin
   if m>abs(s[i]-s[j]) then
   begin
    l1:=i;
    l2:=j;
    m:=abs(s[i]-s[j]);
    end;
  end;
  writeln(m);
  write(l1,' ',l2);
end.