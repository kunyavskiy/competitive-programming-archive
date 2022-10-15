{$APPTYPE CONSOLE}

var st:array[1..18] of int64;
    i:integer;
    a,b:int64;
    s:string;

function berchartoint64(a:char):int64;
begin
  if a='X' then result:=10
  else result:=ord(a)-ord('0');
end;

function bertoint64(s:string):int64;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=result+st[length(s)-i+1]*berchartoint64(s[i]);
end;

function int64toberchar(a:int64):char;
begin
  if a=10 then result:='X'
  else result:=chr(a+ord('0'));
end;

function int64tober(a:int64):string;
var i:integer;
begin
  result:='';
  for i:=18 downto 1 do
    begin
      result:=result+int64toberchar(a div st[i]);
      a:=a mod st[i];
    end;
  while (length(result)>1) and (result[1]='0') do
     delete(result,1,1);
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  st[1]:=1;
  for i:=2 to 18 do
    st[i]:=st[i-1]*10+1;
  readln(s);
  a:=bertoint64(s);
  readln(s);
  b:=bertoint64(s);
  a:=a*b;
  write(int64tober(a));
end.