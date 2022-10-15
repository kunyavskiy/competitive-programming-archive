{$APPTYPE CONSOLE}

uses
  SysUtils;

var w,h,i,j:integer;
    isob1,isob2:array[1..100] of string;
    log:array['0'..'1','0'..'1'] of char;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(w,h);
  for i:=1 to h do
    readln(isob1[i]);
  for i:=1 to h do
    readln(isob2[i]);
  read(log['0','0']);
  read(log['0','1']);
  read(log['1','0']);
  read(log['1','1']);
  for i:=1 to h do
   begin
    for j:=1 to w do
      write(log[isob1[i][j],isob2[i][j]]);
    writeln;
   end;

end.