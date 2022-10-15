{$APPTYPE CONSOLE}
{$H+}

uses
  SysUtils, Math;

const prost:array[1..55] of integer=(2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,1000);

var k,i,j,last,l:integer;
    s,s1:string;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 readln(k);
 readln(s);
 last:=1;
 while prost[last]<=length(s) do
  inc(last);
 dec(last);
 for i:=1 to k do
  begin
  s1:='';
  for j:=1 to length(s)do s1:=s1+' ';
  for j:=1 to last do
   s1[prost[j]]:=s[j];
  j:=last+1;
  l:=1;
  while j<=length(s) do
  if s1[l]<>' ' then inc(l)
  else
  begin
   s1[l]:=s[j];
   inc(l);
   inc(j);
  end;
  s:=s1;
  end;
  write(s);
end.