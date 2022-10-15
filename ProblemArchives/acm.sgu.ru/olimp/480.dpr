{$APPTYPE CONSOLE}

uses
  math;

var n,m,i,k:integer;
    t:array[1..1000000] of int64;

function divint64(a,b:int64):int64;
begin
  result:=trunc(a/b);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  if n>m then
    begin
      n:=n+m;
      m:=n-m;
      n:=n-m;
    end;
  if n=1 then
    begin
      write(min(1,m-1));
      close(input);
      close(output);
      halt;
    end;
  dec(m);
  dec(n);
  for i:=m downto 1 do
    begin
      t[i]:=divint64(m,i)*divint64(n,i);
      k:=2*i;
      while (k<=m) do
        begin
          t[i]:=t[i]-t[k];
          k:=k+i;
        end;
    end;
  {for i:=1 to 1000000 do
    assert(t[i]>=0,'глюки');}
  write(t[1]+2);
end.