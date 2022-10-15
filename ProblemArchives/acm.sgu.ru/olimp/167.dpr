{$APPTYPE CONSOLE}

uses
  SysUtils, math;

const ans:array[1..100] of integer=(103183,82843,107807,200001,94427,0,135089,132509,73320,102634,200000,200000,200000,200000,28427,0,0,0,0,0,200000,200000,136068,100000,150510,200000,91502,0,0,0,200000,200000,200000,200000,200000,200000,200000,200000,200000,200000,200000,200000,200000,200000,144272,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,150889,200000,200000,200000,200000,200000,200000,171068,100000,100000,100000,100000,100000,100000,154033,200000,200000,200000,200000,200000,133200,0,0,0,0,0,0,0,0,0,0,26334,200000,200000,200000,200000,200000);

var i,j,kol:integer;
    a,b:int64;

function good(a:int64):boolean;
var s:string;
begin
  a:=a*a;
  s:=inttostr(a);
  result:=s[1]=s[length(s)];
end;

function sqrtint64(a:int64):int64;
var l,r,m:int64;
begin
  l:=-1;
  r:=a+1;
  while (r-l<>1) do
    begin
       m:=(r+l) div 2;
       if m*m<a then
           l:=m
       else
           r:=m;
    end;
  result:=r;
end;

function res(a:int64):integer;
begin
  result:=0;
  for i:=1 to (a div 1000000)-1 do
       result:=result+ans[i];
  for i:=(a div 1000000)*1000000 to a do
     if good(i) then
        inc(result);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  {write('contst a:array[1..100] of integer=(');
  for i:=1 to 100 do
    begin
      kol:=0;
      for j:=(i-1)*1000000 to i*1000000-1 do
        if good(j) then
          inc(kol);
      write(kol,',');
    end;
  writeln(')');}
  read(a,b);
  a:=sqrtint64(a);
  b:=sqrtint64(b);
  a:=res(a-1);
  b:=res(b);
  write(max(0,b-a));
end.