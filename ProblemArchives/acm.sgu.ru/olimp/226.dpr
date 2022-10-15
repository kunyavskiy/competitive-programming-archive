{$r-,q-}

uses
   Math, SysUtils;

const osn=10000;
      osnlen=4;
      maxlen=100;

type  tlong=array[0..maxlen] of integer;
var k:array[-1..110,-1..110] of tlong;
    num,a:tlong;
    h,l,i:integer;
    st2:array[0..50] of tlong;
    stack:array[1..100] of boolean;


function  mulshort(a:tlong;b:integer):tlong;
var i,c:integer;
begin
  fillchar(result,sizeof(result),0);
  result[0]:=a[0]+10;
  c:=0;
  for i:=1 to a[0] do
    begin
      c:=c+a[i]*b;
      result[i]:=c mod osn;
      c:=c div osn;
    end;
  result[a[0]+1]:=c;
  while result[result[0]]=0 do dec(result[0]);
end;


procedure push(x:boolean);
begin
  inc(h);
  stack[h]:=x;
end;

function top:boolean;
begin
  if h=0 then
    result:=false;
  result:=result and stack[h];
end;

procedure pop;
begin
  dec(h);
end;

function sum(a,b:tlong):tlong;
var c,i:integer;
begin
  if a[0]=0 then
    begin
      result:=b;
      exit;
    end;
  if b[0]=0 then
    begin
      result:=a;
      exit;
    end;
  fillchar(result,sizeof(result),0);
  c:=0;
  for i:=1 to max(a[0],b[0])+1 do
     begin
      c:=c+a[i]+b[i];
      result[i]:=(c mod osn);
      c:=c div osn;
     end;
  result[0]:=max(a[0],b[0])+1;
  while (result[0]>1) and (result[result[0]]=0) do dec(result[0]);
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

function  moreravn(a,b:tlong):boolean;
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
  result:=true;
end;


procedure readlong(var a:tlong);
var s,s1:string;
    i:integer;
begin
  s:='';
  while not seekeof do
  begin
    read(s1);
    s:=s+s1;
  end;
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

function mulllong(a,b:tlong):tlong;
var i,j:integer;
begin
  fillchar(result,sizeof(result),0);
  result[0]:=a[0]+b[0]+10;
  for i:=1 to a[0] do
    for j:=1 to b[0] do
      begin
        result[i+j-1]:=result[i+j-1]+a[i]*b[j];
        result[i+j]:=result[i+j]+(result[i+j-1] div osn);
        result[i+j-1]:=result[i+j-1] mod osn;
      end;
  while result[result[0]]=0 do dec(result[0]);
end;

function tabl(a,l:integer):tlong;
var i,j:integer;
begin
  if l<a then
     begin
       result[0]:=1;
       result[1]:=0;
       exit;
     end;
  k[0,a][0]:=1;
  k[0,a][1]:=1;
  for i:=1 to l do
   for j:=0 to 50 do
     k[i,j]:=sum(k[i-1,j-1],k[i-1,j+1]);
   result:=k[l,0];
  k[0,a][0]:=1;
  k[0,a][1]:=0;
  result:=mulllong(result,st2[(l-a) div 2]);
end;

function generate(l:integer;var num:tlong):string;
var b:int64;
    lr,j,i:integer;
    t:tlong;
begin
  result:='';
  b:=0;
  for i:=1 to l do
    begin
      if b=l-i+1 then
        begin
         while h<>0 do
          begin
            if top then
              result:=result+')'
            else
               result:=result+']';
              pop;
          end;
          exit;
        end;
      t:=tabl(b+1,l-length(result)-1);
      if moreravn(t,num) then
          begin
            result:=result+'(';
            inc(b);
            push(true);
            continue;
          end;
      num:=rasn(num,t);
      if top=true then
        begin
          t:=tabl(b-1,l-length(result)-1);
          if moreravn(t,num) then
            begin
              result:=result+')';
              pop;
              dec(b);
              continue;
            end;
          num:=rasn(num,t);
          result:=result+'[';
          inc(b);
          push(false);
          continue;
        end;
      if moreravn(t,num) then
        begin
          result:=result+'[';
          inc(b);
          push(false);
          continue;
        end;
      num:=rasn(num,t);
      result:=result+']';
      dec(b);
      pop;
    end;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(l);
  readlong(num);
  fillchar(st2,sizeof(st2),0);
  st2[0][1]:=1;
  st2[0][0]:=1;
  for i:=1 to 50 do
    st2[i]:=mulshort(st2[i-1],2);
  //a:=tabl(0,2*l);
  //if more(num,a) then halt(1) else
    writeln(generate(2*l,num));

end.