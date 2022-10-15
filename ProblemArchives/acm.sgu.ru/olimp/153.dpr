{$APPTYPE CONSOLE}

uses
  SysUtils;

type ver=record
       per:integer;
       buk:char;
       end;

var a:array[1..26] of ver;
    n,k,d,i,j,b:integer;

procedure generate(mask:integer;s:string);
var nextper:array['a'..'z'] of integer;
    i:integer;
    j:char;
begin
  dec(k);
  if k=0 then
    begin
      write(s);
      close(input);
      close(output);
      halt;
    end;
  fillchar(nextper,sizeof(nextper),-1);
  for i:=1 to n do
    if (mask and (1 shl(i-1)))<>0 then
    begin
      if nextper[a[i].buk]=-1 then
        nextper[a[i].buk]:=a[i].per
      else nextper[a[i].buk]:=nextper[a[i].buk] or a[i].per;
    end;
  for j:='a' to 'z' do
    if nextper[j]<>-1 then
      generate(nextper[j],s+j);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,k);
  inc(k);
  for i:=1 to n do
    begin
      read(a[i].buk);
      read(d);
      for j:=1 to d do
        begin
          read(b);
          a[i].per:=a[i].per or (1 shl (b-1));
        end;
      readln;
    end;
  generate((1 shl n)-1,'');
end.