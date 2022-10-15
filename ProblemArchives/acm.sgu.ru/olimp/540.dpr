{$APPTYPE CONSOLE}

uses
  Math;

var ti:array[1..100] of integer;
    maxkol,kol,n,i,j,l,r,t:integer;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(ti[i]);
  read(t);
  maxkol:=0;
  for i:=1 to 1000 do
    begin
      l:=i;
      r:=i+t;
      kol:=0;
      for j:=1 to n do
        if (ti[j]<=r) and (ti[j]>=l) then
          inc(kol);
      maxkol:=max(kol,maxkol)
    end;
  write(maxkol);

end.
