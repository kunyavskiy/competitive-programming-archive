{$APPTYPE CONSOLE}
{$O+}

uses
  Math;

var xorch:integer;
    kom:array[1..100000] of record
                           num,liag:integer;
                           end;

   ok:array[0..(1 shl 18)-1] of boolean;
   t,c:array[1..18] of integer;
   n,m,k,i,j,l,mi:integer;

function st(a:integer):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to m do
    if  a and (1 shl(i-1))<>0 then result:=result+c[i];
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m,k);
  xorch:=(1 shl m)-1;
  for i:=1 to m do
     read(t[i],c[i]);
  for i:=1 to k do
     read(kom[i].num);
  for i:=1 to k do
    for j:=1 to m do
       if kom[i].num mod t[j]=0 then
           kom[i].liag:=kom[i].liag or (1 shl (j-1));
  mi:=maxlongint div 2;
  for i:=1 to m do
     begin
       fillchar(ok,sizeof(ok),false);
       for j:=1 to k do
         if (kom[j].liag and (1 shl (i-1)))<>0 then
              ok[(kom[j].liag  xor xorch) xor (1 shl (i-1))]:=true;
       for j:=(1 shl m)-1 downto 1 do
         if (j and (1 shl (i-1)))=0 then ok[j]:=true;
       for j:=(1 shl m)-1 downto 1 do
          if ok[j] then
              for l:=1 to m do
              ok[j and (not (1 shl (l-1)))]:=true;
       for j:=0 to  (1 shl m)-1 do
         if not ok[j] then
          mi:=min(mi,st(j));
     end;
 if mi = maxlongint div 2 then write(-1)
 else write(mi);
end.