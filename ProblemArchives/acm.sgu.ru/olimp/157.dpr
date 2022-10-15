{$APPTYPE CONSOLE}

uses
  SysUtils;


var s:string;
    i,k,n,lk,rk,j:integer;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  readln(s);
  k:=0;
  for i:=1 to length(s) do
   if s[i]='K' then inc(k);
  lk:=0;
  rk:=0;
  for i:=1 to k do
    if s[i]='K' then inc(lk);
  for i:=length(s) downto length(s)-k+1 do
   if s[i]='K' then inc(rk);
  if lk>=rk then
   begin
    writeln(k-lk);
    i:=1;
    j:=length(s);
     while true do
      begin
        if i>k then break;
        while s[i]='K' do inc(i);
        while s[j]='T' do dec(j);
        if i<=k then writeln(i,' ',j);
        inc(i);
        dec(j);
      end;
   end;
  if lk<rk then
   begin
    writeln(k-rk);
    i:=1;
    j:=length(s);
     while true do
      begin
      if length(s)-j+1>k then break;
        while s[i]='T' do inc(i);
        while s[j]='K' do dec(j);
        if length(s)-j+1<=k then writeln(i,' ',j);
        inc(i);
        dec(j);
      end;
  end;
end.