{$APPTYPE CONSOLE}

var d:array[0..184,0..184] of integer;
    q:array[1..183*183,1..2] of integer;
    n,m,i,j,h,t:integer;
    c:char;

procedure push(x,y:integer);
begin
  inc(t);
  q[t,1]:=x;
  q[t,2]:=y;
end;

function empty:boolean;
begin
  result:=h>t;
end;

procedure pop(var x,y:integer);
begin
  x:=q[h,1];
  y:=q[h,2];
  inc(h);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  h:=1;
  t:=0;
  fillchar(d,sizeof(d),-1);
  for i:=1 to n do
    begin
    for j:=1 to m do
      begin
        read(c);
        if c='1' then
          begin
            d[i,j]:=0;
            push(i,j);
          end;
      end;
    readln;
    end;
  while not empty do
    begin
      pop(i,j);
      if  (i>1) and (d[i-1,j]=-1) then
        begin
          push(i-1,j);
          d[i-1,j]:=d[i,j]+1;
        end;
      if  (j>1) and (d[i,j-1]=-1) then
        begin
          push(i,j-1);
          d[i,j-1]:=d[i,j]+1;
        end;
      if  (i<n) and (d[i+1,j]=-1) then
        begin
          push(i+1,j);
          d[i+1,j]:=d[i,j]+1;
        end;
      if  (j<m) and (d[i,j+1]=-1) then
        begin
          push(i,j+1);
          d[i,j+1]:=d[i,j]+1;
        end;
    end;
  for i:=1 to n do
    begin
      for j:=1 to m do
        write(d[i,j],' ');
      writeln;
    end;
end.