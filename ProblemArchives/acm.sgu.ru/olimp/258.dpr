{$APPTYPE CONSOLE}
{$q+,r+}

uses
  SysUtils;

type abcd=record
       x,y:int64;
       end;
var a,b,n,k:int64;
    r:abcd;
function gcd(a,b:int64):int64;
begin
  if b=0 then begin result:=a; exit; end;
  gcd:=gcd(b,a mod b);
end;

function gcdex(a,b:int64):abcd;
var t:int64;
begin
  if b=0 then
    begin
      result.x:=1;
      result.y:=0;
      exit;
    end;
    result:=gcdex(b,a mod b);
    t:=result.y;
    result.y:=result.x-(a div b)*result.y;
    result.x:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,n);
  if a<0 then
    a:=-((-a) mod n);
  a:=(a+n) mod n;
  if b<0 then
    b:=-((-b) mod n);
  b:=(b+n) mod n;
  k:=gcd(a,n);
  if b mod k<>0 then
    begin
      write('-1');
      exit;
    end;
  a:=a div k;
  b:=b div k;
  n:=n div k;
  r:=gcdex(a,n);
  r.x:=r.x*b;
  r.y:=r.y*b;
  if r.x<0 then
    r.x:=-((-r.x) mod n);
  r.x:=(r.x+n) mod n;
  writeln(r.x);
end.