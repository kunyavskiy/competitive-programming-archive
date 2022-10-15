{$APPTYPE CONSOLE}
{$o-}
uses
  SysUtils;

var a:array[-1..9,-1..9] of boolean;


procedure reading;
var    i,j:integer;
    c:char;
begin

       a[1,1]:=true;
       a[1,2]:=true;
       a[2,1]:=true;
       a[2,2]:=true;
       a[6,1]:=true;
       a[6,2]:=true;
       a[7,1]:=true;
       a[7,2]:=true;
       a[1,6]:=true;
       a[1,7]:=true;
       a[2,6]:=true;
       a[2,7]:=true;
       a[6,6]:=true;
       a[6,7]:=true;
       a[7,6]:=true;
       a[7,7]:=true;
       for i:=1 to 2 do
         for j:=3 to 5 do
           begin
             read(c);
             while not ((c=chr(111)) or (c='.')) do
               read(c);
             a[i,j]:=c=chr(111);
           end;
       for i:=3 to 5 do
         for j:=1 to 7 do
           begin
             read(c);
             while not ((c=chr(111)) or (c='.')) do
               read(c);
             a[i,j]:=c=chr(111);
           end;
       for i:=6 to 7 do
         for j:=3 to 5 do
           begin   
             read(c);
             while not ((c=chr(111)) or (c='.')) do
               read(c);
             a[i,j]:=c=chr(111);
           end;
  for i:=-1 to 9 do
    begin
      a[i,0]:=true;
      a[i,8]:=true;
      a[0,i]:=true;
      a[8,i]:=true;
      a[i,-1]:=true;
      a[i,9]:=true;
      a[-1,i]:=true;
      a[9,i]:=true;

    end;
end;

function cango(x,y:integer):integer;
begin
  if a[x,y]=false then
    begin
      result:=0;
      exit;
    end;
  result:=0;
  if a[x-1,y] and not a[x-2,y] then inc(result);
  if a[x+1,y] and not a[x+2,y] then inc(result);
  if a[x,y-1] and not a[x,y-2] then inc(result);
  if a[x,y+1] and not a[x,y+2] then inc(result);
end;

function kol:integer;
var i,j:integer;
begin
      result:=0;
      for i:=1 to 2 do
         for j:=3 to 5 do
           result:=result+cango(i,j);
       for i:=3 to 5 do
         for j:=1 to 7 do
           result:=result+cango(i,j);
       for i:=6 to 7 do
         for j:=3 to 5 do
           result:=result+cango(i,j);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  reading;
  write(kol);
end.