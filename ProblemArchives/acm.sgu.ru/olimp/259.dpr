{$APPTYPE CONSOLE}
{$o-}




uses
  SysUtils;

type abcd=record
       x,y:int64;
       end;
var a,b,c,k,t,n:int64;
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
  read(c,a,b);
  read(b,t);
  c:=t-c;
  if c<0 then
    begin
      c:=-c;
      a:=-a;
      b:=-b;
    end;
  if c=0 then
    begin
     // halt(1);
      if ((a>=0) and (b<=0)) or ((a<=0) and (b>=0)) then
        begin
          write(-1);
          close(input);
          close(output);
          halt;
       end
      else
        begin
          write(1);
          exit;
        end;
    end;
  if a=0 then
    begin
//      write('nksdnf;sdfnl;mvd;mv');
      if (b>0) and (c mod b=0) then
        begin
          write(-1);
          exit;
        end
      else
        begin
          write(0);
          exit;
        end;
    end;
  if b=0 then
    begin
 //     while true do;
      if (a>0) and (c mod a=0) then
        begin
          write(-1);
          exit;
        end
      else
        begin
          write(0);
          exit;
        end;
    end;
  if (a<0) and (b<0) then
    begin
      write(0);
      exit;
    end;
  k:=gcd(abs(a),abs(b));
  if c mod k<>0 then
     begin
       write(0);
       exit;
     end;
  if ((a>0) and (b<0)) or ((a<0) and (b>0)) then
    begin
      write(-1);
      close(input);
      close(output);
      halt;
    end;
  c:=c div k;
  a:=a div k;
  b:=b div k;
  r:=gcdex(a,b);
  r.x:=r.x*c;
  r.y:=r.y*c;
  if r.y<0 then
   begin
    n:=abs(r.y) div a;
    if r.y+n*a<0 then
      inc(n);
    if (r.x-n*b)<0 then
      begin
        write(0);
        exit;
      end;
    r.y:=r.y+n*a;
    r.x:=r.x-n*b;
   end;
  if r.x<0 then
   begin
    n:=abs(r.x) div b;
    if r.x+n*b<0 then
      inc(n);
    if (r.y-n*a)<0 then
      begin
        write(0);
        exit;
      end;
    r.y:=r.y-n*a;
    r.x:=r.x+n*b;
   end;

  write((r.x div b)+(r.y div a)+1);

end.