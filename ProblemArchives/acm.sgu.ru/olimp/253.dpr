{$APPTYPE CONSOLE}

var n,i,j,ml,ms,ls:integer;
    a:array[1..100] of integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
      ml:=0;
      ms:=1;
      ls:=1;
      for j:=1 to n do
        if a[j]<>0 then
          if j-ls>ml then
            begin
              ml:=j-ls;
              ms:=ls;
              ls:=j+1;
            end
          else ls:=j+1;
      if n-ls+1>ml then
            begin
              ml:=n-ls+1;
              ms:=ls;
            end;
      a[(ms+ms+ml-1) div 2]:=i;
    end;
  for i:=1 to n do
  write(a[i],' ');
end.