{$APPTYPE CONSOLE}

uses
  Math;

var x1,x2,x3,y1,y2,y3,rad,l,r,res:int64;
    i:integer;

procedure newlr(y:int64);
begin
  if y=y3 then
    begin
      l:=x3-rad;
      r:=x3+rad;
    end;
  if y<y3 then
    begin
      while (l-x3)*(l-x3)+(y-y3)*(y-y3)<=rad*rad do dec(l);
      inc(l);
      while (r-x3)*(r-x3)+(y-y3)*(y-y3)<=rad*rad do inc(r);
      dec(r);
    end;
  if y>y3 then
    begin
      while (r-x3)*(r-x3)+(y-y3)*(y-y3)>rad*rad do dec(r);
      while (l-x3)*(l-x3)+(y-y3)*(y-y3)>rad*rad do inc(l);
    end;
end;

function intersec(l1,r1,l2,r2:int64):int64;
var lp,rp:int64;
begin
  lp:=max(l1,l2);
  rp:=min(r1,r2);
  if lp>rp then result:=0
  else
    result:=rp-lp+1;
end;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(x1,y1,x2,y2);
   read(x3,y3,rad);
   l:=x3;
   r:=x3;
   res:=0;
   for i:=y3-rad to y3+rad do
     begin
       newlr(i);
       if (y1<=i) and (i<=y2) then
         res:=res+intersec(x1,x2,l,r);
     end;
   write(res);
end.