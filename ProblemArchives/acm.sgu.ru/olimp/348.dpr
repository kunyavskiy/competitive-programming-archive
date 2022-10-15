{$APPTYPE CONSOLE}
uses
  SysUtils;

var i,k,n,s,j1,j2:integer;
    a:array[1..7500] of integer;
 begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(n);
read(k);
fillchar(a,sizeof(a),0);
for i:=1 to n do read(a[i]);
s:=0;
for i:=1 to n do s:=s+abs(a[i]-k);
s:=s div 2;
writeln(s);
j1:=1;
j2:=1;
for i:=1 to s do
begin
if not (a[j1]>k) then
while a[j1]<=k do inc(j1);
if not (a[j2]<k) then
while a[j2]>=k do inc(j2);
dec(a[j1]);
inc(a[j2]);
writeln(j1,' ',j2);
end;
end.