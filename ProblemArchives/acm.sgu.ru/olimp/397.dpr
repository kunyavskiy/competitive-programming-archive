{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;

var n,m,len,i:integer;
    res:int64;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  res:=0;
  if m=1 then
    begin
      write(n);
      close(input);
      close(output);
      halt;
    end;
  for i:=1 to 1100 do
    begin
      len:=(m-1)*i+1;
      res:=res+max(0,n-len+1);
    end;
  write(res);
end.