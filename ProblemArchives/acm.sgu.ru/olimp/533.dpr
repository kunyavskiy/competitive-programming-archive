{$APPTYPE CONSOLE}

uses
  Math,SysUtils;

var a,b,c:integer;
    s1,s2,s3,s123,s132,s231:string;

function wrongsum (a,b:string):string;
var maxlen,i:integer;
begin
  maxlen:=max(length(a),length(b));
  for i:=length(a)+1 to maxlen do
    a:='0'+a;
  for i:=length(b)+1 to maxlen do
    b:='0'+b;
  result:='';
  for i:=maxlen downto 1 do
    result:=inttostr(strtoint(a[i])+strtoint(b[i]))+result;
end;

procedure norm(var s:string);
begin
  while s[1]='0' do
   delete(s,1,1);
end;

function less(s1,s2:string):boolean;
begin
  if length(s1)>length(s2) then
   begin
     result:=false;
     exit;
   end;
  if length(s1)<length(s2) then
    begin
      result:=true;
      exit;
    end;
  result:=s1<s2;
end;

procedure swap(var s,s1:string);
var t:string;
begin
  t:=s;
  s:=s1;
  s1:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,c);
  s1:=inttostr(a);
  s2:=inttostr(b);
  s3:=inttostr(c);
  s123:=wrongsum(wrongsum(s1,s2),s3);
  s132:=wrongsum(wrongsum(s1,s3),s2);
  s231:=wrongsum(wrongsum(s2,s3),s1);
  norm(s123);
  norm(s132);
  norm(s231);
  if less(s132,s123) then swap(s132,s123);
  if less(s231,s123) then swap(s231,s123);
  if less(s231,s132) then swap(s132,s231);
  if (s123=s132) and (s123=s231) then
    begin
      writeln('NO');
      write(s231);
    end
  else
    begin
      writeln('YES');
      writeln(s123);
      if s132<>s123 then writeln(s132);
      if s231<>s132 then writeln(s231);
    end;
end.