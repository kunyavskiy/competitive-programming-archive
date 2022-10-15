{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math,SysUtils;

var  t:array[0..1 shl 17,0..16] of int64;
     gcdok:array[0..16,0..16] of boolean;
     a:array[1..16] of int64;
     n,m,k:int64;
     i,j:integer;

function len(mask,last:int64):int64;
var i:integer;
begin
  if mask and (1 shl (last-1))<>0 then
    begin
      t[mask,last]:=0;
      result:=0;
      exit;
    end;
  if t[mask,last]<>-1 then
    begin
      result:=t[mask,last];
      exit;
    end;
  if mask=0 then
    begin
      result:=1;
      t[mask,last]:=1;
      exit;
    end;
  result:=0;
  for i:=1 to 16 do
    if (gcdok[i,last]) and ((mask and (1 shl (i-1)))<>0)  then
      result:=result+len(mask xor (1 shl (i-1)),i);
  t[mask,last]:=result;
end;

function gcd(a,b:int64):boolean;
begin
  if b=0 then
    begin
      result:=a>=k;
      exit;
    end;
  result:=gcd(b,a mod b);
end;

procedure generate(need,last,mask:int64);
var i,nmask:integer;
begin
  for i:=1 to 16 do
    if (mask and (1 shl (i-1))<>0) and (gcdok[i,last]) then
      begin
        nmask:=mask xor (1 shl (i-1));
        if t[nmask,i]>=need then
          begin
            write(a[i],' ');
            generate(need,i,nmask);
            exit;
          end
        else
          need:=need-t[nmask,i];
      end;
end;

procedure swap(var a,b:int64);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;

end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m,k);
  for i:=1 to n do
   read(a[i]);
  for i:=1 to n do
    for j:=i+1 to n do
      if a[i]>a[j] then swap(a[i],a[j]);
  for i:=1 to n do
    for j:=1 to n do
      gcdok[i,j]:=gcd(a[i],a[j]);
  for i:=1 to n do
    begin
      gcdok[0,i]:=true;
      gcdok[i,0]:=true;
    end;
  fillchar(t,sizeof(t),-1);
  for i:=0 to ((1 shl n)-1) do
    for j:=0 to n do
      t[i,j]:=len(i,j);
  if t[(1 shl n)-1,0]<m then write(-1)
  else generate(m,0,(1 shl n)-1);
end.