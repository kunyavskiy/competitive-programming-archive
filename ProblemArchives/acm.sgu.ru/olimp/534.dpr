{$APPTYPE CONSOLE}

uses
  Math,SysUtils;

var s,sc:string;
    t:array[1..50001] of int64;
    k,c:int64;
    n,i,j:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,c,k);
  k:=trunc(power(10,k));
  readln(s);
  s:=s+'$';
  t[n+1]:=1;
  for i:=n downto 1 do
    begin
      j:=0;
      sc:=s[i];
      if sc='0' then
       begin
         t[i]:=t[i+1];
         continue;
       end;
      while (i+j<=n)  and (strtoint(sc)<=c) do
        begin
          t[i]:=(t[i]+t[i+j+1]) mod k;
          inc(j);
          sc:=sc+s[i+j];
        end;
    end;
  write(t[1]);
end.