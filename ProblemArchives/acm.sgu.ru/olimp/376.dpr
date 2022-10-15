{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;
var vers:array[-100..100,-100..100] of integer;
    used:array[1..100,1..4] of boolean;
    d:array[1..100,1..4] of integer;
    g:array[1..100,1..4,1..100,1..4] of integer;
    free,y,m,n,x,i,t,minv,numx,numy,j:integer;
    c:char;

function vertion(x,y:integer):integer;
begin
  if vers[x,y]=-1 then
    begin
      inc(free);
      vers[x,y]:=free;
      result:=free;
      g[free,1,free,2]:=t;
      g[free,2,free,3]:=t;
      g[free,3,free,4]:=t;
      g[free,4,free,1]:=t;
      g[free,2,free,1]:=t;
      g[free,3,free,2]:=t;
      g[free,4,free,3]:=t;
      g[free,1,free,4]:=t;
      exit;
    end;
  result:=vers[x,y];
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(m,t);
  readln(n);
  x:=0;
  y:=0;
  fillchar(g,sizeof(g),1);
  fillchar(vers,sizeof(vers),-1);
  for i:=1 to n do
    begin
      read(c);
      case c of
      'L':begin g[vertion(x,y),1,vertion(x,y-1),1]:=m; dec(y); end;
      'R':begin g[vertion(x,y),3,vertion(x,y+1),3]:=m; inc(y); end;
      'U':begin g[vertion(x,y),2,vertion(x+1,y),2]:=m; inc(x); end;
      'D':begin g[vertion(x,y),4,vertion(x-1,y),4]:=m; dec(x); end;
      end;
    end;
  fillchar(d,sizeof(d),1);
  d[vertion(0,0),1]:=0;
  d[vertion(0,0),2]:=0;
  d[vertion(0,0),3]:=0;
  d[vertion(0,0),4]:=0;
  while true do
    begin
      minv:=maxlongint div 2;
      numx:=0;
      numy:=0;
      for i:=1 to free do
        for j:=1 to 4 do
          if not used[i,j] and   (d[i,j]<minv) then
            begin
              minv:=d[i,j];
              numx:=i;
              numy:=j;
            end;
      if numx=0 then break;
      used[numx,numy]:=true;
      for i:=1 to free do
        for j:=1 to 4 do
          d[i,j]:=min(d[i,j],d[numx,numy]+g[numx,numy,i,j]);
    end;
  write(min(min(d[vertion(x,y),1],d[vertion(x,y),2]),min(d[vertion(x,y),3],d[vertion(x,y),4])));
end.