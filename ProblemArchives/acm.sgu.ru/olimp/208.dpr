{$APPTYPE CONSOLE}
{$H+}

uses
  SysUtils;

var s,maxs:string;
    le,i,m:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not eof do
    begin
      readln(s);
      le:=0;
      for i:=1 to length(s) do
        if s[i]=' ' then
         begin
           if m<=i-le then
            begin
              m:=i-le;
              maxs:=copy(s,le+1,m);
            end;
           le:=i;
        end;
        i:=length(s);
        if m<=i-le then
            begin
              m:=i-le;
              maxs:=copy(s,le+1,m);
            end;
    end;
 write(maxs);
end.