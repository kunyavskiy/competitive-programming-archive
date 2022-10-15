{$apptype console}
{$H+,i-,o+,r-,q-}
uses math,SysUtils;
type int=longint;
var n,i,k:int;
    pr:boolean;
    ns:string;
procedure proverka(ns1:string; var p:int);
var j:int;
begin
   pr:= (p mod 3=0);
   if pr=true then exit;
    for j:=1 to length(ns) do
    if ns[j]='3' then
      begin
      pr:=true;
      exit    ;
      end;
end;
begin
assign(input,'input.txt');
reset(input);
assign(output,'output.txt');
rewrite(output);
read(n);
k:=0;
for i:=1 to n do
  begin
    ns:=inttostr(i);
    proverka(ns,i);
    if pr=true then k:=k+1;
  end;
write(k);
end.