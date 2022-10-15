{$APPTYPE CONSOLE}
{$O-}
uses
  Math;
const base=79531;
      enter=chr(1);
      incl='#include <';
type tex=array of string;
     tfile=record
           name:string;
           text:tex;
           used:byte;
           next,size:integer;
           end;
var tabl:array[1..6500] of tfile;
    h:array[0..base-1] of integer;
    free,i:integer;
    c:char;
    s:tex;

function hash(s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to min(length(s),100) do
    result:=(result*239+ord(s[i])) mod base;
end;


procedure add(n:string;t:tex;a:integer);
var k:integer;
begin
  inc(free);
  tabl[free].name:=n;
  tabl[free].text:=t;
  tabl[free].used:=0;
  tabl[free].size:=a;
  k:=hash(n);
  tabl[free].next:=h[k];
  h[k]:=free;
end;

procedure getfile;
var t,name:string;
    filetext:tex;
    i,j:integer;
begin
  readln(t);
  for i:=1 to length(t) do
    if t[i] in ['A'..'Z'] then
      t[i]:=chr(ord(t[i])+ord('a')-ord('A'));
  i:=3;
  while i<=length(t)-4 do
      if copy(t,i,4)='\..\' then
        begin
          for j:=i-1 downto 1 do
            if t[j]='\' then
              begin
                 delete(t,j,i-j+3);
              end;
        end
      else inc(i);
 name:=t;
 readln(t);
 setlength(filetext,1);
 if t<>'^Z' then
 begin
 setlength(filetext,2);
 filetext[length(filetext)-1]:=t;
 while true do
   begin
     readln(t);
     if t='^Z' then break;
     setlength(filetext,length(filetext)+1);
     filetext[length(filetext)-1]:=t;
   end
 end;
 add(name,filetext,length(filetext)-1);
end;

function filenum(s,pred:string):integer;
var j,i,k,l:integer;
begin
  i:=pos('\',s);
  if (i=0) or  (copy(s,i-1,2)<>':\') then
        for j:=length(pred) downto 1 do
          if pred[j]='\' then
            begin
              delete(pred,j+1,length(pred)-j);
              s:=pred+s;
              break;
            end;
  for i:=1 to length(s) do
    if s[i] in ['A'..'Z'] then
      s[i]:=chr(ord(s[i])+ord('a')-ord('A'));
  i:=1;
  while i<=length(s)-4 do
      if copy(s,i,4)='\..\' then
        begin
          for j:=i-1 downto 1 do
            if s[j]='\' then
              begin
                 delete(s,j,i-j+3);
              end;
        end
      else inc(i);
  k:=hash(s);
  result:=-1;
  l:=h[k];
  while l<>0 do
    begin
     if tabl[l].name=s then
       begin
         result:=l;
         exit;
       end;
     l:=tabl[l].next;
    end;
end;

function obrob(a:integer):tex;
var i,j,k:integer;
    s:string;
    c:tex;
begin
  if a=-1 then
    begin
      setlength(result,0);
      exit;
    end;
  if tabl[a].used=1 then
    begin
      write('Too long file');
      close(input);
      close(output);
      halt;
    end;
  if tabl[a].used=2 then
   begin
     result:=tabl[a].text;
     exit;
   end;
  tabl[a].used:=1;
  result:=tabl[a].text;
  setlength(result,tabl[a].size+1);
  for i:=1 to tabl[a].size do
    begin
      s:=result[i];
      while s[1]=' ' do
        delete(s,1,1);
      while s[length(s)]=' ' do
        delete(s,length(s),1);
      if (copy(s,1,10)=incl) and (s[length(s)]='>') then
         begin
           delete(s,1,10);
           delete(s,length(s),1);
           k:=filenum(s,tabl[a].name);
           c:=obrob(k);
           result[i]:='';
           for j:=1 to length(c)-1 do
             result[i]:=result[i]+enter+c[j];
           delete(result[i],1,1);
         end;
    end;
  tabl[a].used:=2;
end;


procedure writestring(s:string);
var i:integer;
begin
  if s='' then exit;
  for i:=1 to length(s) do
    if s[i]=enter then writeln
    else write(s[i]);
  writeln;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  free:=0;
  while not eof do
    getfile;
  s:=obrob(1);
  for i:=1 to length(s)-1 do
    writestring(s[i]);
end.