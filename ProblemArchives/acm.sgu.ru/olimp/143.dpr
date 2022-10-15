{$APPTYPE CONSOLE}
{$O-,r+,q+}

uses
  SysUtils, Math;

type aray=array[1..30000] of integer;


var a,s,e:aray;
    n,i,sp,ep,k,c:integer;
    cif:char;

procedure swap (var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsort(var c:aray; l,r:integer);
var m,i,j:integer;
begin
  m:=c[random(r-l+1)+l];
  i:=l;
  j:=r;
  while i<=j do
  begin
    while c[i]<m do inc(i);
    while c[j]>m do dec(j);
    if i<=j then
    begin
    swap(c[i],c[j]);
    inc(i);
    dec(j);
    end;
  end;
  if l<j then qsort(c,l,j);
  if i<r then qsort(c,i,r);
end;


begin
  randomize;
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do begin read(cif); a[i]:=strtoint(cif); end;
  read(k);
  for i:=1 to k do
  begin
   read(s[i]);
   read(e[i]);
  end;
  qsort(s,1,k);
  qsort(e,1,k);
  sp:=1;
  ep:=1;
  c:=0;
  for i:=1 to n do
    begin
     while (sp<=k) and (s[sp]=i) do
     begin
       inc(sp);
       inc(c);
     end;
     while (ep<=k) and (e[ep]=i-1) do
     begin
       inc(ep);
       dec(c);
     end;
     a[i]:=(a[i]+c) mod 2;
    end;
  for i:=1 to n do write(a[i]);
end.