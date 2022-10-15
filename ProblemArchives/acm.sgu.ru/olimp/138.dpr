{$APPTYPE CONSOLE}
type cicle=array of integer;

var per:array[1..10001] of cicle;
    n,i,l,k,j:integer;
    a,b:array[1..10000] of integer;
    used:array[1..10000] of boolean;
procedure swap(var a,b:cicle);
var t:cicle ;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsort(l,r:integer);
var m,i,j:integer;
begin
  m:=per[random(r-l+1)+l,0];
  i:=l; j:=r;
  repeat
    while per[i,0] < m do inc(i);
    while per[j,0] > m do dec(j);
    if i<=j then
    begin
      swap(per[i],per[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

function sqrtciclenechet(a:cicle):cicle;
var i:integer;
begin
  setlength(result,a[0]+1);
  result[0]:=a[0];
  for i:=1 to (a[0] shr 1)+1 do
     result[2*i-1]:=a[i];
  for i:=1 to a[0] shr 1 do
    result[2*i]:=a[(a[0] shr 1)+i+1]
end;

function sqrtciclechet(a,b:cicle):cicle;
var i:integer;
begin
  if a[0]<>b[0] then
    begin
      write('No solution');
      close(input);
      close(output);
      halt;
    end;
  setlength(result,2*a[0]+1);
  result[0]:=2*a[0];
  for i:=1 to a[0] do
    begin
      result[2*i-1]:=a[i];
      result[2*i]:=b[i];
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    read(a[i]);
  k:=0;
  for i:=1 to n do
  if not used[i] then
   begin
    inc(k);
    setlength(per[k],1);
    per[k,0]:=0;
    l:=i;
    while not used[l] do
    begin
      used[l]:=true;
      inc(per[k,0]);
      setlength(per[k],per[k,0]+1);
      per[k,per[k,0]]:=l;
      l:=a[l];
    end;
   end;
  qsort(1,k);
  if per[k,0] and 1=0 then
     begin
       setlength(per[k+1],1);
       per[k+1,0]:=0;
     end;
  i:=1;
  while i<=k do
      if (per[i,0] and 1)=0 then
         begin
           per[i]:=sqrtciclechet(per[i],per[i+1]);
           per[i+1,0]:=0;
           inc(i,2);
         end
      else
        begin
          per[i]:=sqrtciclenechet(per[i]);
          inc(i);
        end;
  while i<=k do
   if per[i,0]=0 then
     begin
       swap(per[i],per[k]);
       dec(k);
     end
   else inc(i);
  for i:=1 to k do
    begin
      inc(per[i,0]);
      setlength(per[i],per[i,0]+1);
      per[i,per[i,0]]:=per[i,1];
    end;
  for i:=1 to k do
    for j:=2 to per[i,0] do
       b[per[i,j-1]]:=per[i,j];
  for i:=1 to n do
    write(b[i],' ');
end.