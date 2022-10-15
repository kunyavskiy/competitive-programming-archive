{$APPTYPE CONSOLE}
{$O+}

uses
  SysUtils;

type tlong=array[0..161] of integer;
     tlong10=array[0..551] of integer;

var r,a:tlong;
    r10:tlong10;
    c:char;
    base:integer;
procedure swap(var a,b:tlong);
var t:tlong;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure abssumlong( x,y:tlong;var z:tlong);
var c,i:integer;
begin
  fillchar(z,sizeof(z),0);
  z[0]:=x[0];
  c:=0;
  for i:=1 to 150 do
  begin
    c:=x[i]+y[i]+c;
    z[i]:=c mod base;
    c:=c div base;
  end;
end;

function absbol(const a,b:tlong):boolean;
var i:integer;
begin
  result:=false;
  for i:=150 downto 1 do
  begin
   if b[i]>a[i] then exit;
   if b[i]<a[i] then
     begin
       result:=true;
       exit;
     end;
  end;
end;

procedure absrasnlong(x,y:tlong;var z:tlong);
var c,i:integer;
begin
  if absbol(y,x) then
    swap(x,y);
  fillchar(z,sizeof(z),0);
  z[0]:=x[0];
  c:=0;
  for i:=1 to 150 do
  begin
   c:=x[i]-y[i]+c;
   z[i]:=((c mod base)+base) mod base;
   if c<0 then c:=-1
   else c:=0;
  end;
end;

procedure sumlong (const x,y:tlong;var z:tlong);
begin
  if x[0]=y[0] then abssumlong(x,y,z)
  else absrasnlong(x,y,z);
end;

procedure rasnlong(x,y:tlong; var z:tlong);
begin
  y[0]:=-y[0];
  sumlong(x,y,z);
end;

procedure mullong(x,y:tlong; var z:tlong);
var i,j:integer;
begin
 fillchar(z,sizeof(z),0);
 z[0]:=x[0]*y[0];
 for i:=1 to 150 do
   for j:=1 to 11 do
     begin
     z[i+j-1]:=x[i]*y[j]+z[i+j-1];
     z[i+j]:=z[i+j]+z[i+j-1] div base;
     z[i+j-1]:=z[i+j-1] mod base;
     end;
end;

function chartoint(c:char):integer;
begin
  if c in ['0'..'9'] then result:=ord(c)-ord('0');
  if c in ['a'..'z'] then result:=ord(c)-ord('a')+10;
  if c in ['A'..'Z'] then result:=ord(c)-ord('A')+10;
end;

procedure sums(const x:tlong10; y:integer;var z:tlong10);
var c,i:integer;
begin
  c:=y;
  i:=1;
  while c>0 do
   begin
   z[i]:=x[i]+c;
   c:=z[i] div 10;
   z[i]:=z[i] mod 10;
   inc(i);
   end;
end;

procedure muls(const x:tlong10; y:integer;var z:tlong10);
var c,i:integer;
begin
  c:=0;
  for i:=1 to 550 do
   begin
   c:=x[i]*y+c;
   z[i]:=c mod 10;
   c:=c div 10
   end;
end;

function convert(a:tlong):tlong10;
var i:integer;
begin
  fillchar(result,sizeof(result),0);
  result[0]:=a[0];
  for i:=150 downto 1 do
    begin
      muls(result,base,result);
      sums(result,a[i],result);
    end;
end;

procedure readlong(var a:tlong);
var s:string;
    i:integer;
begin
  fillchar(a,sizeof(a),0);
  readln(s);
  a[0]:=1;
  for i:=1 to length(s) do
    a[length(s)-i+1]:=chartoint(s[i]);
end;

procedure print(const a:tlong10);
var x,i:integer;
begin
  x:=550;
  while (x>0) and (a[x]=0) do dec(x);
  if x=0 then
  begin
  write(0);
  exit;
  end;
  if a[0]=-1 then write('-');
  for i:=x downto 1 do write(a[i]);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(base);
  readlong(r);
  while true do
    begin
      readln(c);
      if c='=' then break;
      readlong(a);
      if c='+' then sumlong(r,a,r);
      if c='-' then rasnlong(r,a,r);
      if c='*' then mullong(r,a,r);
    end;
  r10:=convert(r);
  print(r10);
end.