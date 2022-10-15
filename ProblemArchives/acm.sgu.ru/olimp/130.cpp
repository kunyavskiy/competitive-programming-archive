{$APPTYPE CONSOLE}

uses
  Math, SysUtils;

const base=10;
      maxlen=85;
      baselen=1;

type tlong=array[0..maxlen] of integer;

var s:string;
    n,j,k,i:integer;
    a:array[1..1000] of tlong;
    res:tlong;

function bolabs(const a,b:tlong):boolean;
var i:integer;
begin
  result:=false;
  for i:=maxlen downto 1 do
    begin
    if a[i]>b[i] then
     begin
       result:=true;
       exit;
     end;
   if a[i]<b[i] then exit;
    end;
end;

procedure swap(var a,b:tlong);
var t:tlong;
begin
  t:=a;
  a:=b;
  b:=t;
end;

function bol(const a,b:tlong):boolean;
begin
 if (a[0]=1) and (b[0]=1) then bol:=bolabs(a,b);
 if (a[0]=1) and (b[0]=-1) then bol:=true;
 if (a[0]=-1) and (b[0]=1) then bol:=false;
 if (a[0]=-1) and (b[0]=-1) then bol:=bolabs(b,a);
end;

procedure rasn(x,y:tlong;var z:tlong);
var c,i:integer;
begin
  if bolabs(y,x) then
   swap(x,y);
  c:=0;
  z[0]:=x[0];
  for i:=1 to maxlen do
  begin
    c:=x[i]-y[i]+c;
    z[i]:=((c mod 10)+10) mod 10;
    if c<0 then c:=-1
    else c:=0;
  end;
end;

procedure sum(x,y:tlong; var z:tlong);
var c,i:integer;
begin
  if x[0]<>y[0] then begin rasn(x,y,z); exit; end;
  z[0]:=x[0];
  c:=0;
  for i:=1 to maxlen do
   begin
     c:=x[i]+y[i]+c;
     z[i]:=c mod base;
     c:=c div base;
   end;
end;


procedure qsort(l,r:integer);
var i,j: integer;
    m:tlong;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while bol(m,a[i]) do inc(i);
    while bol(a[j],m) do dec(j);
    if i<=j then
    begin
      swap(a[i],a[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;

procedure print(a:tlong);
var x,i,j:integer;
begin
  x:=maxlen;
  while a[x]=0 do dec(x);
  if x=0 then
    begin
    write(0);
    exit;
    end;
  if a[0]=-1 then write('-');
  for i:=x downto 1 do
   write(a[i]);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,k);
  i:=1;
  for i:=1 to n do
    begin
     readln(s);
     j:=1;
     while j<=length(s) do
      if ((j=1) and (s[j]='-')) or (s[j] in ['0'..'9']) then inc(j)
      else delete(s,j,1);
      j:=1;
      if (length(s)=0) or ((length(s)=1) and (s[1]='-')) then
        begin
         a[i,0]:=1;
         continue;
        end;
      if s[1]='-' then
        begin
        a[i,0]:=-1;
        delete(s,1,1);
        end
      else a[i,0]:=1;
      for j:=length(s) downto 1 do
        a[i,j]:=strtoint(s[length(s)-j+1]);
    end;
  qsort(1,n);
  fillchar(res,sizeof(res),0);
  res[0]:=1;
  for i:=1 to k do
    sum(res,a[i],res);
  print(res);
end.