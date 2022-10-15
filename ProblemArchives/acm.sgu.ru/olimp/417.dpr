{$APPTYPE CONSOLE}
uses
  SysUtils;
var c,c1:char;
    a:array[1..26] of integer;
    n,i,j:integer;
    q: boolean;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 readln(n);
 for i:=1 to n do
 begin
 read(c);
 inc(a[ord(c)-ord('A')+1]);
 end;
 q:=false;
 for i:=1 to 26 do
 begin
 if q=true then a[i]:=a[i]-a[i] mod 2;
 if a[i] mod 2=1 then q:=true;
 end;
 c1:='1';
 for i:=1 to 26 do
  begin
 case i of
 1:c:='A';
 2:c:='B';
 3:c:='C';
 4:c:='D';
 5:c:='E';
 6:c:='F';
 7:c:='G' ;
 8:c:='H';
 9:c:='I';
 10:c:='J';
 11:c:='K';
 12:c:='L';
 13:c:='M';
 14:c:='N';
 15:c:='O';
 16:c:='P';
 17:c:='Q';
 18:c:='R';
 19:c:='S';
 20:c:='T';
 21:c:='U';
 22:c:='V';
 23:c:='W';
 24:c:='X';
 25:c:='Y';
 26:c:='Z';
 end;
  for j:=1 to a[i] div 2 do write(c);
  if a[i] mod 2 =1 then c1:=c;
 end;
 if not (c1='1') then write(c1);
  for i:=26 downto 1 do
  begin
 case i of
 1:c:='A';
 2:c:='B';
 3:c:='C';
 4:c:='D';
 5:c:='E';
 6:c:='F';
 7:c:='G';
 8:c:='H';
 9:c:='I';
 10:c:='J';
 11:c:='K';
 12:c:='L';
 13:c:='M';
 14:c:='N';
 15:c:='O';
 16:c:='P';
 17:c:='Q';
 18:c:='R';
 19:c:='S';
 20:c:='T';
 21:c:='U';
 22:c:='V';
 23:c:='W';
 24:c:='X';
 25:c:='Y';
 26:c:='Z';
 end;
  for j:=1 to a[i] div 2 do write(c);
 end;
end.