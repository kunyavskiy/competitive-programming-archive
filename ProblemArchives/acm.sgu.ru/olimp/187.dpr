{$APPTYPE CONSOLE}

uses
  SysUtils;



var used:array[0..999] of integer;
    n,a,b,k,p,t,i:integer;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,n);
  a:=a mod n;
  k:=a;
  p:=1;
  while (p<b) and (used[a]=0) do
  begin
  used[a]:=p;
  inc(p);
  a:=(a*k) mod n;
  end;
  if p=b then
  begin
    write(a);
    close(input);
    close(output);
    halt;
  end;
  t:=p-used[a];
  b:=(b-p) mod t;
  for i:=1 to b do
    a:=(a*k) mod n;
  write(a);
end.