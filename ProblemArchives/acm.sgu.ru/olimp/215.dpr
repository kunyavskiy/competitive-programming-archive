{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  maxprime = 10;

type
  Tstep = array[1..10]of byte;

var
  prime:array[1..maxprime+1]of byte = (2,3,5,7,11,13,17,19,23,29,1);
  N,maxdel,maxnum:int64;
  s:tstep;

procedure init(num:int64;p:byte);
var
  i:byte;
  del:integer;
begin
  if p<=maxprime then
  begin
    for i:=p to maxprime+1 do
    begin
      if num*prime[i]<=n then
      begin
        inc(s[i]);
        init(num*prime[i],i);
        dec(s[i]);
      end;
    end;
  end
  else
  begin
    del:=1;
    for i:=1 to maxprime do
      del:=del*(s[i]+1);
    if del = maxdel then
      if maxnum > num then maxnum:=num;
    if del > maxdel then
    begin
      maxdel:=del;
      maxnum:=num;
    end;
  end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');

  readln(n);

  maxnum:=1;
  maxdel:=1;
  init(1,1);

  write(maxnum);

  close(input);
  close(output);
end.