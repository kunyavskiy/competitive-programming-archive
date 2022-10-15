{$APPTYPE CONSOLE}

uses
  SysUtils;



type  abcd=array[1..1000] of boolean;
      day=record
           good:integer;
           stuf:abcd;
         end;

var res:abcd;
    resbad:abcd;
    days:array[1..1000] of day;
    kol1,kol2,kol3,n,m,k,i,j,a,numbad:integer;

function orarray(a,b:abcd):abcd;
var i:integer;
begin
  for i:=1 to m do
    result[i]:=a[i] or b[i];
end;

procedure  qsort(l,r:integer);
var i,j,m:integer;
    t:day;
begin
  m:=days[random(r-l+1)+l].good;
  i:=l;
  j:=r;
  while i<=j do
    begin
      while days[i].good<m do inc(i);
      while days[j].good>m do dec(j);
      if i<=j then
        begin
          t:=days[i]; days[i]:=days[j]; days[j]:=t;
          inc(i);
          dec(j);
        end;
    end;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    begin
      read(days[i].good);
      read(k);
      for j:=1 to k do
        begin
          read(a);
          days[i].stuf[a]:=true;
        end;
    end;
  qsort(1,n);
  fillchar(res,sizeof(res),false);
  k:=n+1;
  for i:=1 to n do
    begin
      if days[i].good=1 then begin k:=i; break; end;
      res:=orarray(res,days[i].stuf);
    end;
  for i:=1 to m do
    if res[i] then inc(kol1);
  for i:=k to n do
    begin
      numbad:=0;
      for j:=1 to m do
        if (days[i].stuf[j]) and (not res[j]) then
           if numbad=0 then numbad:=j
           else begin numbad:=0; break end;
      if numbad<>0 then  resbad[numbad]:=true;
    end;
  for i:=1 to m do
    if resbad[i] then inc(kol2);
  write(kol1,' ',kol2,' ',m-kol1-kol2);
end.