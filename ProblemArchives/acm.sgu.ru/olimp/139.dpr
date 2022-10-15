{$APPTYPE CONSOLE}
{$H+}
{$O-}

uses
  SysUtils, Math;

var a:array[1..26] of integer;
    s:string;
    i:integer;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 fillchar(a,sizeof(a),0);
 while not eof do
  begin
   readln(s);
   for i:=1 to length(s) do
    begin
    if (ord(s[i])<=ord('z')) and (ord(s[i])>=ord('a'))  then
       inc(a[ord(s[i])-ord('a')+1]);
    if (ord(s[i])<=ord('Z')) and (ord(s[i])>=ord('A'))  then
        inc(a[ord(s[i])-ord('A')+1]);
     end;
  end;
 for i:=1 to 26 do
   if a[i]=maxintvalue(a) then write(chr(ord('A')+i-1));
end.