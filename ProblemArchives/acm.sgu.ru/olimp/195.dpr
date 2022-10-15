{$APPTYPE CONSOLE}

uses
  Math;

var x,y,z,vx,vy,vz,k,l:int64;
    ux,uy,uz,d,u,a,b,c,t:real;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(x,y,z);
   read(vx,vy,vz);
   read(u);
   if y<>0 then
   begin
     a:=x*x+y*y+z*z;
     k:=vy*x-vx*y;
     l:=vy*z-vz*y;
     b:=-2*k*x-2*l*z;
     c:=k*k+l*l-y*y*u*u;
     d:=b*b-4*a*c;
     uy:=(-b+sqrt(d))/(2*a);
     t:=(uy-vy)/y;
     if t<0 then uy:=(-b-sqrt(d))/(2*a);
     ux:=(uy*x-k)/y;
     uz:=(uy*z-l)/y;
     write(ux:0:2,' ',uy:0:2,' ',uz:0:2);
   end
   else
     if x<>0 then
       begin
         uy:=vy;
         u:=sqrt(u*u-uy*uy);
         k:=z*vx-x*vz;
         a:=x*x+z*z;
         b:=2*k*z;
         c:=k*k-x*x*u*u;
         d:=b*b-4*a*c;
         ux:=(-b+sqrt(d))/(2*a);
         uz:=(ux*z-k)/x;
         write(ux:0:2,' ',uy:0:2,' ',uz:0:2);
       end
     else
       begin
         uy:=vy;
         ux:=vx;
         uz:=sqrt(u*u-ux*ux-uy*uy);
         write(ux:0:2,' ',uy:0:2,' ',uz:0:2)
       end;
end.