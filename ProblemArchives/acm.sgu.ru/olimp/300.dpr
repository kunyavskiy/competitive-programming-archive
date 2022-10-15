{$APPTYPE CONSOLE}

var s:string;
    a:array[0..9] of integer;
    b:array[1..9] of integer;
    lb,la,i,j:integer;
procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure print(s:string);
var i,j,k:integer;
begin
  if lb=0 then
    begin
      write(s);
      close(input);
      close(output);
      halt;
    end;
  if a[b[lb]]=0 then
  begin
    for i:=b[lb]-1 downto 0 do
      if a[i]<>0 then
        begin
          write(s);
          write(i);
          dec(a[i]);
          for j:=9 downto 0 do
           for k:=1 to a[j] do
            write(j);
          close(input);
          close(output);
          halt;
        end;
    exit;
  end;
  s:=s+chr(ord('0')+b[lb]);
  dec(a[b[lb]]);
  dec(lb);
  print(s);
  delete(s,length(s),1);
  inc(a[b[lb+1]]);
  inc(lb);
  for i:=b[lb]-1 downto 1 do
    if a[i]<>0 then
      begin
        write(s);
        write(i);
        dec(a[i]);
        for j:=9 downto 0 do
          for k:=1 to a[j] do
          write(j);
        close(input);
        close(output);
        halt;
      end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  la:=length(s);
  for i:=1 to la do
    inc(a[ord(s[i])-ord('0')]);
  readln(s);
  lb:=length(s);
  for i:=1 to lb do
    b[lb-i+1]:=ord(s[i])-ord('0');
  if la<lb then
  begin
    for i:=9 downto 0 do
      for j:=1 to a[i] do write(i);
    close(input);
    close(output);
    halt;
  end;
  print('');
end.