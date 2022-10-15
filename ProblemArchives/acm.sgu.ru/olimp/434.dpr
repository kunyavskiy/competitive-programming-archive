{$APPTYPE CONSOLE}
{$I-,O+,R-,Q-}
uses
  SysUtils;
var x,a,y:real;
    res:integer;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(x);
read(y);
if (y>0) and (x>0)then
  begin
  a:=arctan(y/x);
  a:=(a/pi)*180;
  if a<9 then res:=6
  else if  (a<27) then res:=13
    else if  (a<45) then res:=4
      else if  (a<63) then res:=18
          else if  (a<81) then res:=1
            else res:=20;
  end
else
  if (y>0) and (x<0) then
  begin
    a:=arctan(y/x);
    a:=(a/pi)*180;
    a:=a*(-1);
    a:=90-a;
  if a<9 then res:=20
  else if  (a<27) then res:=5
    else if  (a<45) then res:=12
      else if  (a<63) then res:=9
          else if (a<81) then res:=14
            else res:=11;
  end
   else if(y<0) and(x<0) then
    begin
      a:=arctan(y/x);
      a:=(a/pi)*180;
    if a<9 then res:=11
    else if (a<27) then res:=8
      else if  (a<45) then res:=16
        else if  (a<63) then res:=7
            else if  (a<81) then res:=19
              else res:=3;
  end
   else
   if (y<0) and (x>0) then
  begin
    a:=arctan(y/x);
    a:=(a/pi)*180;
    a:=90+a;
  if a<9 then res:=3
  else if (a<27) then res:=17
    else if (a<45) then res:=2
      else if (a<63) then res:=15
          else if (a<81) then res:=10
            else res:=6;
  end
  else if x=0 then
          if y>=0 then res:=20
            else res:=3
      else if y=0 then
         if x>=0 then res:=6
          else res:=11;
a:=sqrt(sqr(x)+sqr(y));
if a<6.35 then res:=50
  else if a<15.9 then res:=25
    else if (a<107) and (a>99) then res:=res*3
      else if (a<170) and (a>162) then res:=res*2
        else if (a>170) then res:=0;
write(res)
end.