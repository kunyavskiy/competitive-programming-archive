{$APPTYPE CONSOLE}
{$R+,q+}
uses
  Math;


 var a:array[1..700,1..700] of boolean;
     n,i,j,l:integer;
     c:char;
     res:int64;

function sum (a:integer):int64;
begin
  result:=a*(a+1) div 2;
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  res:=0;
  for i:=1 to n do
   begin
    for j:=1 to n do
     begin
       read(c);
       if c=chr(46) then
         begin
           dec(res);
           a[i,j]:=true;
         end
       else
         if c=chr(35) then
         a[i,j]:=false
         else
          halt(1);
     end;
       readln;
    end;
  for i:=1 to n do
   begin
     l:=1;
     for j:=1 to n do
       if not a[i,j] then
         begin
           res:=res+sum(j-l);
           l:=j+1;
         end;
     res:=res+sum(n-l+1);
   end;
   for j:=1 to n do
   begin
     l:=1;
     for i:=1 to n do
       if not a[i,j] then
         begin
           res:=res+sum(i-l);
           l:=i+1;
         end;
     res:=res+sum(n-l+1);
   end;
  write(res);

end.