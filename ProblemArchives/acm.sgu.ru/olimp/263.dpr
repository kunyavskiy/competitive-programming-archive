{$APPTYPE CONSOLE}

uses
  SysUtils;

type tlong=array[1..251] of integer;

var a,b:tlong;
    c,i,kolmove,j:integer;
procedure readlong(var a:tlong);
var s:string;
   i,l:integer;
begin
  readln(s);
  l:=length(s);
  for i:=1 to l do
    a[l-i+1]:=ord(s[i])-ord('0');
end;

function sum(a,b:tlong):tlong;
var c,i:integer;
begin
  c:=0;
  for i:=1 to 251 do
    begin
      c:=c+a[i]+b[i];
      result[i]:=c mod 10;
      c:=c div 10;
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readlong(a);
  readlong(b);
  b:=sum(a,b);
  read(c);
  kolmove:=0;
  for i:=1 to c-1 do
    if a[i]<>b[i] then
      begin
        write('No solution');
        close(input);
        close(output);
        halt;
      end;
  for i:=c to 251 do
    begin
      if a[i]=b[i] then
      begin
        inc(kolmove);
        continue;
      end;
      for j:=1 to kolmove do
        writeln('move');
      kolmove:=0;
      for j:=1 to (((b[i]-a[i])+10) mod 10) do
        writeln('+');
     inc(kolmove);
    end;

end.