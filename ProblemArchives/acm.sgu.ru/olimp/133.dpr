{$APPTYPE CONSOLE}

var n,k,a,b,a1,b1,k1:int64;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k,n);
  read(a,b);
  k1:=k mod n;
  a1:=(a div n)*n +k1;
  if a1<a then a1:=a1+n;
  b1:=(b div n)*n +k1;
  if b1>b then b1:=b1-n;
  if k<=a then write((b1-a1) div n+1);
  if (k>a) and (k<=b) then write((b1-k) div n+1);
  if k>b then write(0);
end.