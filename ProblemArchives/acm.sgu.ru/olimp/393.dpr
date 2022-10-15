{$APPTYPE CONSOLE}
{$H+}
uses
  SysUtils;
var n,k,i:integer;
    st:string;
procedure sled(var s1:string);
var s,s2:string;c:char;k,num:integer;
begin
s:=s1;
s1:='';
num:=1;
s[length(s)+1]:=' ';
repeat
c:=s[num];
k:=0;
while s[num]=c do
begin
inc(k);
inc(num);
end;
s2:=inttostr(k);
s1:=s1+s2+c;
until num>length(s);
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
readln(n);
read(k);
st:=inttostr(n);
for i:=1 to k-1 do sled(st);
write(st);
end.