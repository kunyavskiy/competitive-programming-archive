{$APPTYPE CONSOLE}

var s:string;
    i,ls,h:integer;
    ex:array[1..100] of integer;
function palin(s:string):boolean;
var i:integer;
begin
  result:=true;
  for i:=1 to length(s) do
    if s[i]<>s[length(s)-i+1] then
      begin
        result:=false;
        exit;
      end;
end;

function pochtypalin(s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    if palin(copy(s,1,i-1)+copy(s,i+1,length(s)-i)) then
     result:=i;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  s:=' '+s+' ';
  ls:=0;
  h:=0;
  for i:=1 to length(s) do
      if s[i]=' ' then
        begin
          if ls<>i-1 then
            begin
              inc(h);
              ex[h]:=pochtypalin(copy(s,ls+1,i-ls-1));
            end;
          ls:=i;
        end;
  writeln(h);
  for i:=1 to h do
    write(ex[i],' ');
end.