{$APPTYPE CONSOLE}

uses
  SysUtils;

type zigzag=record
      up,down:integer;
      end;

var t,from:array[1..1000] of zigzag;
    used:array[1..1000] of boolean;
    kolmax,n,i,j,max,maxnum,maxtype,ln,lt:integer;
    a:array[1..1000] of integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  fillchar(used,sizeof(used),false);
  fillchar(from,sizeof(from),0);
  for i:=1 to n do
     read(a[i]);
  for i:=1 to n do
    begin
      t[i].up:=1;
      t[i].down:=1;
      for j:=1 to n-1 do
        begin
          if a[i]>a[j] then
            if t[i].up<t[j].down+1 then
              begin
                t[i].up:=t[j].down+1;
                from[i].up:=j;
              end;
          if a[i]<a[j] then
            if t[i].down<t[j].up+1 then
              begin
                t[i].down:=t[j].up+1;
                from[i].down:=j;
              end;
        end;
    end;
  for i:=1 to n do
    begin
      if t[i].up>max then
        begin
          max:=t[i].up;
          maxnum:=i;
          maxtype:=1;
        end;
     if t[i].down>max then
        begin
          max:=t[i].down;
          maxnum:=i;
          maxtype:=2;
        end;
    end;
  used[maxnum]:=true;
  ln:=maxnum;
  lt:=maxtype;
  while ln<>0 do
    begin
      if lt=1 then
        ln:=from[ln].up
      else ln:=from[ln].down;
      lt:=3-lt;
      used[ln]:=true;
    end;
  for i:=1 to n do
    if not used[i] then inc(kolmax);
  writeln(kolmax);
  for i:=1 to n do
    if not used[i] then write(i,' ');
end.