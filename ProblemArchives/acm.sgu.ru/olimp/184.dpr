{$APPTYPE CONSOLE}
{$R+,Q+}

var a:array[-1..202,-1..202] of char;
    b:array[-1..202,-1..202] of boolean;
    n,i,j,kol:integer;
    a1:char;

procedure korol(x,y:integer);
var i,j:integer;
begin
  for i:=-1 to 1 do
   for j:=-1 to 1 do
    if a[x+i,y+j] in [' ','b'] then b[x+i,y+j]:=true;
end;

procedure ladia (x,y:integer);
var i:integer;
begin
 for i:=x+1 to n do
  begin
   if a[i,y] in [' ','b'] then b[i,y]:=true;
   if a[i,y]<>' ' then break
  end;
 for i:=x-1 downto 1 do
  begin
   if a[i,y] in [' ','b'] then b[i,y]:=true;
   if a[i,y]<>' ' then break
  end;
  for i:=y+1 to n do
  begin
   if a[x,i] in [' ','b'] then b[x,i]:=true;
   if a[x,i]<>' ' then break
  end;
 for i:=y-1 downto 1 do
  begin
   if a[x,i] in [' ','b'] then b[x,i]:=true;
   if a[x,i]<>' ' then break
  end;
end;

procedure slon (x,y:integer);
var i:integer;
begin
 i:=1;
 while (x+i<=n) and (y+i<=n) do
 begin
  if a[x+i,y+i] in ['b',' '] then b[x+i,y+i]:=true;
  if a[x+i,y+i]<>' ' then break;
  inc(i);
 end;
 i:=1;
 while (x-i>=1) and (y+i<=n) do
 begin
  if a[x-i,y+i] in ['b',' '] then b[x-i,y+i]:=true;
  if a[x-i,y+i]<>' ' then break;
  inc(i);
 end;
 i:=1;
 while (x+i<=n) and (y-i>=1) do
 begin
  if a[x+i,y-i] in ['b',' '] then b[x+i,y-i]:=true;
  if a[x+i,y-i]<>' ' then break;
  inc(i);
 end;
 i:=1;
 while (x-i>=1) and (y-i>=1) do
 begin
  if a[x-i,y-i] in ['b',' '] then b[x-i,y-i]:=true;
  if a[x-i,y-i]<>' ' then break;
  inc(i);
 end;
end;

procedure fers (x,y:integer);
begin
  ladia(x,y);
  slon(x,y);
end;

procedure kon (x,y:integer);
var i,j:integer;
begin
 for i:=-2 to 2 do
  for j:=-2 to 2 do
   if (abs(i)+abs(j)=3) and (a[x+i,y+j] in ['b',' ']) then
     b[i+x,j+y]:=true;
end;

procedure peshca (var x,y:integer);
begin
 if a[x-1,y+1] in ['b',' '] then b[x-1,y+1]:=true;
 if a[x-1,y-1] in ['b',' '] then b[x-1,y-1]:=true;
end;

procedure bit (c:char;x,y:integer);
begin
 case c of
 'K':korol(x,y);
 'F':fers(x,y);
 'L':ladia(x,y);
 'S':slon(x,y);
 'H':kon(x,y);
 'P':peshca(x,y);
 end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
 for i:=-1 to n+2 do
   begin
   a[-1,i]:='.';
   a[n+2,i]:='.';
   a[i,-1]:='.';
   a[i,n+2]:='.';
   end;
  for i:=1 to n do
   begin
     for j:=1 to n do
     begin
      read(a1);
      if a1 in ['K','F','L','S','H','P'] then
        a[i,j]:=a1
      else
        if a1 in ['k','f','l','s','h','p'] then a[i,j]:='b'
       else a[i,j]:=' ';
     end;
     readln;
   end;
  for i:=1 to n do
    for j:=1 to n do
      bit(a[i,j],i,j);
  kol:=0;
  for i:=1 to n do
    for j:=1 to n do
     if b[i,j] then inc(kol);
  write(kol);
end.