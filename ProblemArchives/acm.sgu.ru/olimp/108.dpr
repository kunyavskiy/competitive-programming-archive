{$APPTYPE CONSOLE}



uses
  SysUtils;

var  a:array[0..5000] of int64;
     p:array[1..100] of integer;
     n,k,j,m,i,c:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    begin
      read(c);
      inc(p[c])
    end;
   a[0]:=1;
   for k:=1 to 100 do
      for j:=m downto 1 do
        for i:=1 to p[k] do
           if j>=i*k then a[j]:=a[j]+a[j-i*k] else break;
   write(a[m]);
end.