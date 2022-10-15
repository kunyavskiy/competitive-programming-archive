{$APPTYPE CONSOLE}

uses
  SysUtils;

type tlong=array[0..90] of shortint;

var list:array[1..1000] of tlong;
    res:tlong;
    n,k,i,x:integer;

function sumabs(a,b:tlong):tlong;
var c,i:integer;
begin
  c:=0;
  result[0]:=a[0];
  for i:=1 to 90 do
    begin
      c:=c+a[i]+b[i];
      result[i]:=c mod 10;
      c:=c div 10;
    end;
end;

function rasnabs(a,b:tlong):tlong;
var c,i:integer;
begin
  c:=0;
  result[0]:=a[0];
  for i:=1 to 90 do
    begin
      c:=c+a[i]-b[i];
      result[i]:=(c+100) mod 10;
      if c<0 then
        c:=-1
      else
        c:=0;
    end;
end;


function bolabs(a,b:tlong):boolean;
var i:integer;
begin
  for i:=90 downto 1 do
   begin
    if a[i]>b[i] then
      begin
        result:=true;
        exit;
      end;
    if a[i]<b[i] then
      begin
        result:=false;
        exit;
      end;
   end;
  result:=false;
end;

function sum(a,b:tlong):tlong;
begin
  if a[0]=b[0] then
    begin
     result:=sumabs(a,b);
     exit;
    end;
  if bolabs(a,b) then
    begin
      result:=rasnabs(a,b);
      exit;
    end;
  result:=rasnabs(b,a);
end;

procedure readlong(var a:tlong);
var s:string;
    i:integer;
begin
  fillchar(a,sizeof(a),0);
  readln(s);
  i:=1;
  while i<=length(s) do
    if s[i] in ['0'..'9','-'] then inc(i)
    else
      delete(s,i,1);
  i:=2;
  while i<=length(s) do
    if s[i] in ['0'..'9'] then inc(i)
    else
      delete(s,i,1);
  if s[1]='-' then
   begin
     a[0]:=-1;
     delete(s,1,1);
   end
  else
     a[0]:=1;
  for i:=length(s) downto 1 do
    a[length(s)-i+1]:=ord(s[i])-ord('0');
end;

procedure swap(var a,b:tlong);
var t:tlong;
begin
  t:=a;
  a:=b;
  b:=t;
end;

function bol(a,b:tlong):boolean;
begin
  if a[0]<b[0] then
    begin
      result:=false;
      exit;
    end;
  if a[0]>b[0]then
     begin
       result:=true;
       exit;
     end;
  for i:=90 downto 1 do
   begin
    if a[i]>b[i] then
      begin
        result:=true xor (a[0]=-1);
        exit;
      end;
    if a[i]<b[i] then
      begin
        result:=false xor (a[0]=-1);
        exit;
      end;
   end;
  result:=false;
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m:tlong;
begin
  i:=l;
  j:=r;
  m:=list[random(r-l+1)+l];
  while i<=j do
    begin
      while bol(m,list[i]) do
       inc(i);
      while bol(list[j],m) do
           dec(j);
      if i<=j then
        begin
          swap(list[i],list[j]);
          inc(i);
          dec(j);
        end;
    end;
  if (l<j)  then qsort(l,j);
  if (i<r)  then qsort(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,k);
  for i:=1 to n do
    readlong(list[i]);
  if k<>n then qsort(1,n);
  fillchar(res,sizeof(res),0);
  for i:=1 to k do
    res:=sum(res,list[i]);
  x:=90;
  while (x>=1) and (res[x]=0) do dec(x);
  if x=0 then
    begin
      write(0);
      close(input);
      close(output);
      halt;
    end;
  if res[0]=-1 then
    write('-');
  for i:=x downto 1 do write(res[i]);

end.