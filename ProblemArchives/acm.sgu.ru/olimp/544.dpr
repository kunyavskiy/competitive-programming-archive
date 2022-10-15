{$APPTYPE CONSOLE}

uses
  Math;

var s,spr,sword:string;
    w,i,teclen,karr:integer;
    ress:array[1..2000] of string;




begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(w);
  readln(s);
  i:=1;
  karr:=1;
  while i<=length(s) do
    begin
      sword:='';
      spr:='';
      while (i<=length(s)) and (s[i]=' ') do
        begin
          spr:=spr+' ';
          inc(i);
        end;     
      while (i<=length(s)) and (s[i]<>' ') do
        begin
          sword:=sword+s[i];
          inc(i);
        end;
      if sword='' then break;
      if length(sword)>w then
         begin
           close(input);
           close(output);
           halt;
         end;
      if length(ress[karr]+spr+sword)<=w then
         begin
          if length(ress[karr])=0 then
            begin
              ress[karr]:=ress[karr]+sword;
              continue;
            end;
          ress[karr]:=ress[karr]+spr+sword;
          continue;
         end;
      if length(ress[karr])=0 then
            begin
              ress[karr]:=ress[karr]+sword;
              continue;
            end;
      inc(karr);
      ress[karr]:=sword;
    end;
  for i:=1 to karr do
      writeln(ress[i]);
end.
