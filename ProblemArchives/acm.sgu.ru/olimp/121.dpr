{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;

var  i,yklw,ykrw,xkw,yklb,ykrb,xkb,xw,xb,yw,yb,xbw,ybw,l,r,n,xlen,res:integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure makeotrw(k:integer; var l,r:integer);
var k1:integer;
begin
  k1:=abs(xkw-xw)-k;
  l:=max(max(yklw-k1,yw-k),1);
  r:=min(min(ykrw+k1,yw+k),n);
end;

procedure makeotrb(k:integer; var l,r:integer);
var k1:integer;
begin
  k1:=abs(xkb-xb)-k;
  l:=max(max(yklb-k1,yb-k),1);
  r:=min(min(ykrb+k1,yb+k),n);
end;

function cango (x,l,r,k:integer):integer;
var lbw,rbw:integer;
begin
   if abs(xbw-x)>k then
     begin
       result:=maxlongint div 2;
       exit;
     end;
   if abs(xbw-x)=k then
     begin
       lbw:=max(ybw-k,1);
       rbw:=min(ybw+k,n);
       if max(l,lbw)<=min(r,rbw) then
          begin
            result:=k;
            exit;
          end
       else
         begin
           result:=maxlongint div 2;
           exit;
         end;
     end;
   if abs(xbw-x)<k then
     begin
       lbw:=ybw-k;
       rbw:=ybw+k;
       result:=maxlongint div 2;
       if (lbw>0) and (lbw<=r) and (lbw>=l) then
         result:=k;
       if (rbw<=n) and (rbw<=r) and (rbw>=l) then
         result:=k;
       exit;
     end;
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  read(xb,yb);
  read(xw,yw);
  read(xbw,ybw);
  if abs(xw-xb)<abs(yw-yb) then
    begin
      swap(xb,yb);
      swap(xw,yw);
      swap(xbw,ybw);
    end;
  xlen:=abs(xb-xw)-1;
  if xlen=0 then
    begin
      writeln('NO');
      write(0);
      exit;
    end;
  if xb<xw then
    begin
      xkb:=xb+(xlen div 2);
      xkw:=xw-(xlen div 2)-(xlen mod 2);
    end
  else
    begin
      xkb:=xb-(xlen div 2);
      xkw:=xw+(xlen div 2)+(xlen mod 2);
    end;
  yklw:=max(yw-abs(xw-xkw),1);
  ykrw:=min(yw+abs(xw-xkw),n);
  yklb:=max(yb-abs(xb-xkb),1);
  ykrb:=min(yb+abs(xb-xkb),n);
  yklw:=max(max(yklw,yklb-1),1);
  yklb:=max(max(yklb,yklw-1),1);
  ykrw:=min(min(ykrw,ykrb+1),n);
  ykrb:=min(min(ykrb,ykrw+1),n);
  res:=maxlongint div 2;
  if xb<xw then
    begin
      for i:=xb+1 to xkb-1 do
        begin
          makeotrb(i-xb,l,r);
          res:=min(res,cango(i,l,r,i-xb));
        end;
      if xlen mod 2=1 then
         begin
           makeotrb(xkb-xb,l,r);
           res:=min(res,cango(xkb,l,r,xkb-xb));
         end;
      for i:=xw-1 downto xkw+1 do
        begin
          makeotrw(xw-i,l,r);
          res:=min(res,cango(i,l,r,xw-i));
        end;
    end
  else
    begin
       for i:=xw+1 to xkw-1 do
        begin
          makeotrw(i-xw,l,r);
          res:=min(res,cango(i,l,r,i-xw));
        end;
      if xlen mod 2=1 then
         begin
           makeotrb(xkb-xb,l,r);
           res:=min(res,cango(xkb,l,r,xkb-xb));
         end;
      for i:=xb-1 downto xkb+1 do
        begin
          makeotrb(xb-i,l,r);
          res:=min(res,cango(i,l,r,xb-i));
        end;
    end;
  if res=maxlongint div 2 then
    begin
      writeln('NO');
      write(xlen);
    end
  else
    begin
      writeln('YES');
      writeln(res);
    end;
end.