{$APPTYPE CONSOLE}

uses
   Math, SysUtils;

const osn=100000000;
      osnlen=8;
      maxlen=130;

type  tlong=array[0..maxlen] of integer;
var k:array[-1..110,-1..110] of tlong;
    num,a:tlong;
    l:integer;

{function  mulshort(a:tlong;b:integer):tlong;
var i,c:integer;
begin
  fillchar(result,sizeof(result),0);
  c:=0;
  for i:=1 to maxlen do
    begin
      c:=c+a[i]*b;
      result[i]:=c mod osn;
      c:=c div osn;
    end;
end;}

function sum(a,b:tlong):tlong;
var c,i:integer;
begin
  fillchar(result,sizeof(result),0);
  c:=0;
  for i:=1 to max(a[0],b[0])+1 do
     begin
      c:=c+a[i]+b[i];
      result[i]:=(c mod osn);
      c:=c div osn;
     end;
  result[0]:=max(a[0],b[0])+1;
  while result[result[0]]=0 do dec(result[0]);
end;

function rasn(a,b:tlong):tlong;
var i,c:integer;
begin
  fillchar(result,sizeof(result),0);
  c:=0;
  for i:=1 to max(a[0],b[0]) do
    begin
      c:=c+a[i]-b[i];
      result[i]:=(c+osn) mod osn;
      if c<0 then c:=-1
      else c:=0;
    end;
  result[0]:=max(a[0],b[0]);
  while result[result[0]]=0 do dec(result[0]);
end;

function  more(a,b:tlong):boolean;
var i:integer;
begin
  if a[0]>b[0] then
    begin
      result:=true;
      exit;
    end;
  if a[0]<b[0] then
    begin
      result:=false;
      exit;
    end;
  for i:=a[0] downto 1 do
    begin
      if a[i]>b[i] then begin  result:=true; exit; end;
      if a[i]<b[i] then begin result:=false; exit; end;
    end;
  result:=false;
end;

procedure readlong(var a:tlong);
var s:string;
    i:integer;
begin
  readln(s);
  i:=1;
  while length(s)>osnlen do
     begin
       a[i]:=strtoint(copy(s,length(s)-osnlen+1,osnlen));
       delete(s,length(s)-osnlen+1,osnlen);
       inc(i);
     end;
  a[i]:=strtoint(s);
  a[0]:=i;
  while a[a[0]]=0 do
     dec(a[0]);
end;

procedure writelong(a:tlong);
var i,x,j,k:integer;
begin
  x:=maxlen;
  while a[x]=0 do dec(x);
  write(a[x]);
  dec(x);
  for i:=x downto 1 do
    begin
      if a[i]=0 then
        begin
          for j:=1 to osnlen do write(0);
          continue;
        end;
      k:=trunc(log10(a[i]))+1;
      for j:=1 to osnlen-k do
        write(0);
      write(a[i]);
    end;
end;

function tabl(a,l:integer):tlong;
var i,j:integer;
begin
  k[0,a][0]:=1;
  k[0,a][1]:=1;
  for i:=1 to l do
   for j:=0 to 50 do
     k[i,j]:=sum(k[i-1,j-1],k[i-1,j+1]);
   result:=k[l,0];
  k[0,a][0]:=0;
  k[0,a][1]:=0;
end;

procedure generate(l:integer;var num:tlong);
var b:int64;
    lr:integer;
    t:tlong;
begin
  lr:=0;
  while lr<l do
  begin
  write('(');
  inc(lr);
  b:=1;
  while b>0 do
    begin
      t:=tabl(b+1,l-lr-1);
      if more(t,num) then
          begin
            write('(');
            inc(lr);
            inc(b);
          end
      else
          begin
            write(')');
            num:=rasn(num,t);
            inc(lr);
            dec(b);
          end;
    end;
  end;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(l);
  readlong(num);
  a:=tabl(0,2*l);
  if more(num,a) then write('No solution for this testcase.') else
  begin
    generate(2*l,num);
    a[1]:=1;
    a[0]:=1;
    num:=rasn(num,a);
  end;
end.