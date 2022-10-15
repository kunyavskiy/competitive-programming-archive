{$APPTYPE CONSOLE}
{$H+}

uses
  SysUtils;

var kol,n,m,i,j:integer;
    a:array[0..101,0..101] of integer;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    for j:=1 to m do
      read(a[i,j]);
  kol:=0;
  for i:=1 to n do
    begin
     a[i,0]:=0;
     a[i,m+1]:=0;
    end;
  for i:=1 to m do
    begin
     a[0,i]:=0;
     a[n+1,i]:=0;
    end;
  for i:=1 to n do
    for j:=1 to m do
      begin
        if a[i,j]=1 then
        begin
          if a[i-1,j]=1 then
            begin
            if a[i,j-1]=1 then inc(kol);
            if a[i,j+1]=1 then inc(kol);
            end;
          if a[i+1,j]=1 then
            begin
            if a[i,j-1]=1 then inc(kol);
            if a[i,j+1]=1 then inc(kol);
            end;
        end
     end;
  write(kol);
end.