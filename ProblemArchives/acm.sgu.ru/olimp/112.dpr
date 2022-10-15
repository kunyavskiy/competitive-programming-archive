{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

var k,n,m,kkol:int64;
    i:integer;
    c:string;
    a:array[1..15] of integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(k);
  i:=0;
  readln(c);
  for i:=1 to length(c) do
    a[i]:=strtoint(c[i]);
  n:=length(c);;
  m:=10;
  kkol:=0;
  for i:=1 to n do
   if a[i]=k then inc(kkol);
  if kkol=n then
    begin
     if n=1 then write(10)
     else write(n*k+1);
     close(input);
     close(output);
     halt;
    end;
  for i:=1 to n do
    if a[i]<>k then m:=min(a[i],m);
  if m<k then
    begin
     write(kkol*(m+1));
     close(input);
     close(output);
     halt;
    end;
  if kkol=1 then
    begin
     write(m+1);
     close(input);
     close(output);
     halt;
    end;
  if kkol=0 then
    begin
     write(0);
     close(input);
     close(output);
     halt;
    end;
  write(kkol*k+1);
end.