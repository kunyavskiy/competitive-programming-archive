program Project1;

{$APPTYPE CONSOLE}

uses
  Math;

var f:array[0..15] of int64;
    n,m,i,r:integer;
    s:string;

function soch(n,m:integer):int64;
begin
  if m>n then
     begin
       result:=0;
       exit;
     end;
  result:=trunc(f[n]/f[m]);
  result:=trunc(result/f[n-m]);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  readln(s);
  m:=length(s);
  f[0]:=1;
  for i:=1 to 15 do
    f[i]:=f[i-1]*i;
  r:=0;
  for i:=0 to min(m,n) do
    r:=r+(n-i)*soch(m-1,i);
  write(r);
end.