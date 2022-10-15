{$APPTYPE CONSOLE}

uses
  SysUtils;

type tlong=array[1..10000] of integer;

var s,s1,s2:string;
    a,b,c:tlong;
    base,z,i,len,x:integer;

procedure mullong(const a,b:tlong; var c:tlong);
var i,j:integer;
begin
  fillchar(c,sizeof(c),0);
  for i:=1 to 2499 do
    for j:=1 to 2499 do
       begin
         c[i+j-1]:=a[i]*b[j]+c[i+j-1];
         c[i+j]:=c[i+j]+c[i+j-1] div base;
         c[i+j-1]:=c[i+j-1] mod base;
       end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(z);
  s:='';
  s1:='';
  s2:='';
  for i:=1 to z do
    s:=s+'1';
  for i:=1 to 140 do
    s1:=s1+'0';
  for i:=z downto 2 do
    begin
    insert(s1,s,i);
    delete(s1,length(s1),1);
    end;
  write(s,'*');
  for i:=length(s) downto 1 do
    s2:=s2+s[i];
  write(s2,'=');
  len:=length(s)*2+2;
  for i:=length(s) downto 1 do
    a[length(s)-i+1]:=strtoint(s[i]);
  for i:=length(s) downto 1 do
    b[length(s)-i+1]:=strtoint(s2[i]);
  base:=z;
  mullong(a,b,c);
  x:=5000;
  while c[x]=0 do dec(x);
  for i:=x downto 1 do
   begin
    write(c[i]);
 {if c[i]>1 then writeln;
    inc(len);}
   end;
   writeln;
 {write(len);}
end.