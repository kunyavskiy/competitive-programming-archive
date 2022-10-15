{$APPTYPE CONSOLE}
{$MINSTACKSIZE 16000000}

uses
  Math;

var t:array[1..10000] of int64;
    tb1000:array[1..10000] of record
                             del,st:int64;
                             end;
    h,a,i:integer;
    r:int64;
    c:char;
procedure raslup(n:integer);
var i:integer;
begin
  i:=2;
  while i<=trunc(sqrt(n))  do
    begin
       while n mod i=0  do
        begin
          inc(t[i]);
          n:=n div i;
        end;
        inc(i);
      end;
      if (n>1) and (n<=10000) then inc(t[n]);
      if n>10000 then
      begin
        for i:=1 to h do
          if tb1000[i].del=n then
            begin
              inc(tb1000[i].st);
              exit;
            end;
        inc(h);
        tb1000[h].del:=n;
        tb1000[h].st:=1;
      end;
end;

procedure rasldown(n:integer);
var i:integer;
begin
  i:=2;
  while i<=trunc(sqrt(n))  do
    begin
       while n mod i=0  do
        begin
          dec(t[i]);
          n:=n div i;
        end;
        inc(i);
      end;
    if (n>1) and (n<=10000) then dec(t[n]);
      if n>10000 then
      begin
        for i:=1 to h do
          if tb1000[i].del=n then
            begin
              dec(tb1000[i].st);
              exit;
            end;
        inc(h);
        tb1000[h].del:=n;
        tb1000[h].st:=-1;
      end;
end;




begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a);
  h:=0;
  raslup(a);
  while not seekeof do
    begin
      read(c);
      if not (c in ['/','*']) then
         begin
           write('adffgdf');
           close(input);
           close(output);
           halt;
         end;
      read(a);
      if c='*' then raslup(a);
      if c='/' then rasldown(a);
    end;
  r:=1;
  for i:=1 to 10000 do
    r:=(r*(t[i]+1)) mod 100000;
  for i:=1 to h do
    r:=(r*(tb1000[i].st+1)) mod 100000;
  write(r);
end.