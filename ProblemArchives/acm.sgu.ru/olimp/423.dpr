{$APPTYPE CONSOLE}

uses
  Math;

var a:array[1..600] of string;
    n,i,j:integer;
    em:string;

procedure swap(var a,b:string);
var t:string;
begin
  t:=a;
  a:=b;
  b:=t;
end;

function bolchar(a,b:char):boolean;
begin
  if (a<>'\') and(b<>'\') then
    begin
      result:=a>b;
      exit;
    end;
  result:= (b='\');
end;

function bols(a,b:string):boolean;
var i:integer;
begin
  for i:=1 to min(length(a),length(b)) do
      if a[i]<>b[i] then
        begin
         result:=bolchar(a[i],b[i]);
         exit;
        end;
  result:=length(a)>length(b)
end;


procedure qsorts(l,r:integer);
var i,j:integer;
    t,m:string;
begin
  m:=a[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while bols(m,a[i]) do inc(i);
    while bols(a[j],m) do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsorts(l,j);
  if i<r then qsorts(i,r);
end;


function print(deep:integer;var num:integer; dir:string):boolean;
var s,copydir:string;
    i,j:integer;
begin
  copydir:=dir;
  s:=a[num];
  if copy(s,1,length(dir))<>dir then
    begin
     result:=false;
     exit;
    end;
  result:=true;
  i:=length(dir)+1;
  while (i<length(s)) and (s[i]<>'\') do inc(i);
  for j:=1 to deep do write(' ');
  if copy(s,length(dir)+1,i-length(dir)-1)<>'a' then writeln(copy(s,length(dir)+1,i-length(dir)-1));
  dir:=copy(s,1,i);
  if length(dir)=length(s) then
    begin
      inc(num);
      print(deep,num,copydir);
      exit;
    end;
  while (num<=n) and print(deep+1,num,dir) do;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do
    begin
     readln(a[i]);
     a[i]:=a[i]+'\';
    end;
  qsorts(1,n);
  i:=1;
  while i<n do
    begin
      if a[i]=copy(a[i+1],1,length(a[i])) then
        begin
          for j:=i to n-1 do
            swap(a[j],a[j+1]);
          dec(n);
        end
      else inc(i);
    end;
  for i:=1 to n do
     a[i]:='a\'+a[i];
  em:='';
  i:=1;
  print(-1,i,'');
end.