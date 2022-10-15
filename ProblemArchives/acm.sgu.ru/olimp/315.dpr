{$APPTYPE CONSOLE}
{$r+,q+,h+}

uses sysutils;


var t:array[0..200,0..200]of string;
    s:string;
    i:integer;

function min(s,s1:string):string;
begin
  if length(s)<=length(s1) then result:=s
  else result:=s1;
end;

function sjat(s:string):string;
var l,j,i:integer;
    p:array[0..200] of integer;
begin
   p[1]:=0;
   l:=length(s);
   for i:=2 to l do
     begin
       j:=p[i-1];
       while (j<>0) and (s[j+1]<>s[i]) do
             j:=p[j];
       p[i]:=j;
       if (s[j+1]=s[i]) then inc(p[i]);
     end;
   j:=l-p[l];
   if (l mod j=0) and (j<>l) then
      result:='('+inttostr(l div (l-p[l]))+copy(s,1,l-p[l])+')'
   else
     result:=s;
end;

function beststring(l,r:integer):string;
var i:integer;
begin
  if l>r then
    begin
      result:='';
      exit;
    end;
  if t[l,r]<>'' then
    begin
      result:=t[l,r];
      exit;
    end;
  if l=r then
    begin
      result:=s[l];
      t[l,r]:=s[l];
      exit;
    end;
  result:=copy(s,l,r-l+1);
  result:=min(result,sjat(result));
  for i:=l to r-1 do
     result:=min(result,beststring(l,i)+beststring(i+1,r));
  t[l,r]:=result;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  //i:=1;
  //while i<=length(s) do
   // if s[i]=' ' then
    //  delete(s,i,1)
    //else inc(i);
  writeln(beststring(1,length(s)));
end.