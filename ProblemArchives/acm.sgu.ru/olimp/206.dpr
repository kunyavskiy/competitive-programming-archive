{$APPTYPE CONSOLE}

uses
  SysUtils;

var p:array[1..10] of integer;
    n,a,b,i:integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure swaparray(l,r:integer);
var i:integer;
begin
  for i:=l to ((l+r) div 2) do
    swap(p[i],p[r+l-i]);
end;

procedure next;
var k,t:integer;
begin
  k:=n;
  repeat
    dec(k)
  until(k=0) or (p[k]<p[k+1]);
  if k=0 then
  begin
    close(input);
    close(output);
    halt;
  end;
  t:=n;
  while (p[t]<p[k]) do dec(t);
   swap(p[k],p[t]);
  swaparray(k+1,n);
end;

procedure sum;
var s,i:integer;
begin
  s:=0;
  for i:=1 to n do
    s:=s+p[i]*i;
  if (s>=a) and (s<=b) then
    begin
      for i:=1 to n do
         write(p[i],' ');
       writeln;
    end;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,a,b);
  for i:=1 to n do
    p[i]:=i;
  sum;
  while true do
    begin
      next;
      sum;
    end;
end.