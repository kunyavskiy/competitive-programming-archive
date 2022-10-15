{$APPTYPE CONSOLE}
var b,k,s,i:integer;
function predprost(a:integer):boolean;
var j,l:integer;
begin
if trunc(sqrt(a))=sqrt(a) then
begin
predprost:=false;
exit;
end;
l:=0;
for j:=1 to trunc(sqrt(a)) do
if a mod j=0 then inc(l);
predprost:=(l=2);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(k);
s:=0;
b:=1;
for i:=1 to k do
begin
  while not predprost(b) do inc(b);
  s:=s+b;
  inc(b);
end;
write(s);
end.