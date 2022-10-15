{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

var n,m,k,i:integer;
    a:array[1..100,1..2] of integer;
    s:string;
    p:array[1..2] of integer;
    res:array[1..200] of integer;

function supermax(p1,p2:integer):integer;
begin
if p1>n then
  begin
   supermax:=2;
   exit;
  end;
if p2>m then
  begin
   supermax:=1;
   exit;
  end;
if a[p1,1]>a[p2,2] then
  begin
   supermax:=1;
   exit;
  end;
if a[p2,2]>a[p1,1] then
  begin
   supermax:=2;
   exit;
  end;
supermax:=supermax(p1+1,p2+1);
end;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 readln(s);
 fillchar(a,sizeof(a),1);
 n:=length(s);
 for i:=1 to length(s) do
  a[i,1]:=strtoint(s[i]);
 readln(s);
 m:=length(s);
 for i:=1 to length(s) do
   a[i,2]:=strtoint(s[i]);
 p[1]:=1;
 p[2]:=1;
 for i:=1 to n+m do
   begin
   k:=supermax(p[1],p[2]);
   res[i]:=a[p[k],k];
   inc(p[k]);
   end;
 for i:=1 to n+m do write(res[i]);
end.