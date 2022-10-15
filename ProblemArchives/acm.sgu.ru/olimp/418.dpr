{$APPTYPE CONSOLE}



uses
  Math;

const xjump:array[1..8] of integer=(2,2,-2,-2,1,1,-1,-1);
      yjump:array[1..8] of integer=(1,-1,1,-1,2,-2,2,-2);
var  a:array[1..15,1..15] of char;
     d:array[1..15,1..15] of integer;
     qx,qy:array[1..250] of integer;
     n,m,t,h,i,j,xh,yh,xs,ys:integer;
     c:char;


function canjump(x,y,t:integer):boolean;
var xj,yj:integer;
begin
  xj:=x+xjump[t];
  yj:=y+yjump[t];
  if (0>=xj) or (n<xj) or (0>=yj) or (m<yj) or (a[xj,yj]<>'.') or (d[xj,yj]<>-1) then
    begin
      result:=false;
      exit;
    end;
  result:=false;
  case t of
  1: if ((a[x+1,y] in ['.','+']) and (a[x+2,y] in ['.','+'])) then  result:=true
     else
       if ((a[x,y+1] in ['.','+']) and (a[x+1,y+1] in ['.','+'])) then  result:=true
       else   result:=false;
  2: if ((a[x+1,y] in ['.','+']) and (a[x+2,y] in ['.','+'])) then  result:=true
     else
       if((a[x,y-1] in ['.','+']) and (a[x+1,y-1] in ['.','+'])) then  result:=true
     else   result:=false;
  3:if ((a[x-1,y] in ['.','+']) and (a[x-2,y] in ['.','+'])) then result:=true
    else if((a[x,y+1] in ['.','+']) and (a[x-1,y+1] in ['.','+'])) then  result:=true
    else result:=false;
  4:if ((a[x-1,y] in ['.','+']) and (a[x-2,y] in ['.','+'])) then  result:=true
    else if((a[x,y-1] in ['.','+']) and (a[x-1,y-1] in ['.','+'])) then  result:=true
     else result:=false;
  5:if ((a[x,y+1] in ['.','+']) and (a[x,y+2] in ['.','+'])) then  result:=true else
      if ((a[x+1,y] in ['.','+']) and (a[x+1,y+1] in ['.','+'])) then  result:=true else
      result:=false;
  6:if ((a[x,y-1] in ['.','+']) and (a[x,y-2] in ['.','+'])) then  result:=true else
     if   ((a[x+1,y] in ['.','+']) and (a[x+1,y-1] in ['.','+'])) then  result:=true else
      result:=false;
  7:if ((a[x,y+1] in ['.','+']) and (a[x,y+2] in ['.','+'])) then  result:=true else
     if   ((a[x-1,y] in ['.','+']) and (a[x-1,y+1] in ['.','+'])) then  result:=true else
      result:=false;
  8:if ((a[x,y-1] in ['.','+']) and (a[x,y-2] in ['.','+'])) then  result:=true else
     if   ((a[x-1,y] in ['.','+']) and (a[x-1,y-1] in ['.','+'])) then  result:=true else
      result:=false
  else halt(1);
  end;
end;

procedure push(x,y:integer);
begin
  qx[t]:=x;
  qy[t]:=y;
  inc(t);
end;

procedure pop(var x,y,k:integer);
begin
  x:=qx[k];
  y:=qy[k];
end;

function empty:boolean;
begin
  result:=t=h;
end;

procedure bfs(x,y:integer);
var i,j:integer;
begin
   j:=1;
   t:=1;
   push(x,y);
   d[x,y]:=0;
   while j<=t do
      begin
        pop(x,y,j);
        for i:=1 to 8 do
          if canjump(x,y,i) then
            begin
              push(x+xjump[i],y+yjump[i]);
              d[x+xjump[i],y+yjump[i]]:=d[x,y]+1;
            end;
        inc(j);
      end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do
    begin
    for j:=1 to m do
      begin
        read(c);
        if c in['.','+','*'] then a[i,j]:=c else
        if c='h' then
          begin
            if (xh<>0) or (yh<>0) then halt(1);
            xh:=i;
            yh:=j;
            a[i,j]:='.';
          end else
        if c='s' then
          begin
           if (xs<>0) or (ys<>0) then halt(1);
           xs:=i;
           ys:=j;
           a[i,j]:='.';
          end else
           halt(1);
      end;
      readln;
    end;
  fillchar(d,sizeof(d),-1);
  bfs(xs,ys);
  write(d[xh,yh]);
end.