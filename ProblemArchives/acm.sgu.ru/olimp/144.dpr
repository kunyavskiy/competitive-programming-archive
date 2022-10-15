{$APPTYPE CONSOLE}

uses
  Math;

var b:array[0..(1 shl 21)-1] of integer;
    d:array[0..(1 shl 21)-1] of record
                                bmask,pod:integer;
                                end;
    a,mask:array[1..21] of integer;
    n,m,i,k,s,j,ma,mamask,makol:integer;

function kol (mask:integer):integer;
begin
  result:=0;
  while mask>0 do
    begin
      inc(result);
      mask:=mask-trunc(power(2,trunc(log2(mask))));
    end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    read(a[i]);
  b[0]:=0;
  k:=0;
  for i:=1 to trunc(power(2,n))-1 do
    begin
      if i and (1 shl (k))=0 then inc(k);
      b[i]:=b[i and (not (1 shl k))]+a[k+1];
    end;
  for i:=1 to m do
    begin
     read(s);
     for j:=1 to s do
       begin
         read(k);
         mask[i]:=mask[i] or (1 shl (k-1));
       end;
      read(a[i]);
    end;
  k:=0;
  for i:=1 to trunc(power(2,m)-1) do
    begin
      if i and (1 shl (k))=0 then inc(k);
      d[i].pod:=d[i and (not (1 shl k))].pod+a[k+1];
      d[i].bmask:=d[i and (not (1 shl k))].bmask or mask[k+1];
    end;
  ma:=0;
  makol:=0;
  mamask:=0;
  for i:=1 to trunc(power(2,m))-1 do
      if (d[i].pod-b[d[i].bmask]>ma) or ((d[i].pod-b[d[i].bmask]=ma) and (kol(d[i].bmask)<makol)) then
        begin
          mamask:=d[i].bmask;
          ma:=d[i].pod-b[d[i].bmask];
          makol:=kol(d[i].bmask);
        end;
  writeln(ma);
  k:=0;
  writeln(makol);
  for i:=0 to n-1 do
    if (mamask and (1 shl i))<>0 then write(i+1,' ');

end.