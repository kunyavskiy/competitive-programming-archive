//{$APPTYPE CONSOLE}

uses
  math;

var slov:array[1..100] of string;
    text:string;
    t:array[0..1000] of integer;
    from:array[0..1000] of string;
    i,j,n,ras,l:integer;

function makesmall(a:char):char;
begin
  if a in ['a'..'z'] then
    result:=a
  else
    result:=chr(ord(a)-ord('A')+ord('a'));
end;
function makebig(a:char):char;
begin
  if a in ['A'..'Z'] then
    result:=a
  else
    result:=chr(ord(a)+ord('A')-ord('a'));
end;

function destchar(a,b:char):integer;
begin
  a:=makesmall(a);
  b:=makesmall(b);
  if a<b then
    result:=min(ord(b)-ord(a),26-ord(b)+ord(a))
  else
    result:=min(ord(a)-ord(b),26-ord(a)+ord(b))
end;

function deststring(a,b:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(a) do
    result:=result+destchar(a[i],b[i]);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do
      readln(slov[i]);
  readln(text);
  fillchar(t,sizeof(t),1);
  t[0]:=0;
  for i:=1 to length(text) do
    from[i]:='$';
  from[0]:='';
  for i:=0 to length(text) do
    if from[i]<>'$' then
         for j:=1 to n do
         begin
           l:=length(slov[j]);
           if i+l<=length(text) then
             begin
               ras:=deststring(slov[j],copy(text,i+1,l));
               if t[i]+ras<t[i+l] then
                 begin
                   from[i+l]:=from[i]+slov[j];
                   t[i+l]:=t[i]+ras;
                 end;
             end;
         end;
  if from[length(text)]='$' then
    write(-1)
  else
  for i:=1 to length(text) do
    if text[i] in ['a'..'z'] then
      write(makesmall(from[length(text)][i]))
    else
     write(makebig(from[length(text)][i]))

end.