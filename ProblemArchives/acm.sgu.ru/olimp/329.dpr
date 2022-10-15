{$apptype console}
{$O+}
uses sysutils,math;
var m,a3,b3,i,nod,a,b:longint;
    s1,s2:string;
    c:char;
    q:boolean;
procedure swap (var a,b:longint);
var t:longint;
begin
t:=a;
a:=b;
b:=t;
end  ;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
read(c);
read(c);
while not eof do
begin
read(c);
if (not q)  and not (c='(')then s1:=s1+c
else
if (c='(') then q:=true
else
if q and not ((c='(') or (c=')')) then s2:=s2+c
else break
end;
if not (s1='') then
a3:=strtoint(s1+s2)-strtoint(s1)
else a3:=strtoint(s2);
b3:=0;
for i:=1 to length(s2) do b3:=b3*10 +9;
for i:=1 to length(s1) do b3:=b3*10;
a:=a3;
b:=b3;
 while not(a mod b =0) do
 begin
 a:=a mod b;
 swap(a,b);
 end;
 a3:=a3 div b;
 b3:= b3 div b;
write(a3,'/',b3);
end.