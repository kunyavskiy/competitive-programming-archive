{$APPTYPE CONSOLE}
uses
  SysUtils;
type pole=record
      up:boolean;
      down:boolean;
      left:boolean;
      right:boolean;
      end;
var a:array[1..201,1..201] of pole;
    i,j,t:integer;
    c:char;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');;
for i:=1 to 201 do
  for j:=1 to 201 do
  begin
  a[i,j].up:=false;
  a[i,j].down:=false;
  a[i,j].left:=false;
  a[i,j].right:=false;
  end;
i:=101;
j:=101;
t:=0;
while not eof do
begin
read(c);
case c of
'N':begin
    if a[i,j].up=true then inc(t)
      else inc(t,5);
    a[i,j].up:=true;
    inc(i);
    a[i,j].down:=true;
        end;
'S':begin
    if a[i,j].down=true then inc(t)
      else inc(t,5);
    a[i,j].down:=true;
    dec(i);
    a[i,j].up:=true;
    end;
'W':begin
    if a[i,j].left=true then inc(t)
      else inc(t,5);
    a[i,j].left:=true;
    dec(j);
    a[i,j].right:=true;
    end;
'E':begin
    if a[i,j].right=true then inc(t)
      else inc(t,5);
    a[i,j].right:=true;
    inc(j);
    a[i,j].left:=true;
    end;
end;
end;
write(t);
end.