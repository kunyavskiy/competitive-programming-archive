{$APPTYPE CONSOLE}

uses
  SysUtils;
var stack:array[1..45150] of integer;
    h,n,i,a,obkol,m,mnum:integer;
    kol:array[1..300] of integer;

procedure push(x:integer);
begin
  inc(h);
  stack[h]:=x;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
    begin
     read(a);
     inc(kol[a]);
    end;
  obkol:=n;
  while obkol<>0 do
    begin
    m:=kol[1];
    mnum:=1;
     for i:=2 to 300 do
     if kol[i]>m then
     begin
      m:=kol[i];
      mnum:=i;
     end;
    push(mnum);
    if mnum=1 then obkol:=obkol-kol[1]
    else kol[mnum-1]:=kol[mnum-1]+kol[mnum];
    kol[mnum]:=0;
    end;
   writeln(h);
   for i:=1 to h do write(stack[i],' ');
end.