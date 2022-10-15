{$APPTYPE CONSOLE}
{$R+,Q+}

uses SysUtils;

var a:array[0..9] of integer;
    c:char;
    i,j:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not seekeof do
   begin
     read(c);
     inc(a[strtoint(c)]);
   end;
  for i:=1 to 10 do
    begin
      if i=10 then
        begin
          write(0);
          exit;
        end;
      if a[i]<>0 then
        begin
          write(i);
          dec(a[i]);
          break;
        end;
    end;
  for i:=0 to 9 do
    for j:=1 to a[i] do
      write(i);
end.