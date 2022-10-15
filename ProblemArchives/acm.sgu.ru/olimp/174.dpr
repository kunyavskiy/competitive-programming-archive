{$APPTYPE CONSOLE}
{$R+,Q+}
type    point=record
            x,y:int64;
            end;
        event=record
          time,num:integer;
          place:point;
        end;

var a:array[0..1000] of event;
    t,from:array[0..1000] of integer;
    ok:array[1..1000] of boolean;
    n,i,j,l:integer;

procedure qsort(l,r:integer);
var m,i,j:integer;
    t:event;
begin
  m:=a[random(r-l+1)+l].time;
  i:=l; j:=r;
  repeat
    while a[i].time<m do inc(i);
    while a[j].time>m do dec(j);
    if i<=j then
    begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;




function dest2(a,b:point):real;
begin
  result:=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
end;


function findmaxnum:integer;
var i:integer;
begin
  result:=0;
  for i:=1 to n do
    if t[i]>t[result] then result:=i;
  writeln(t[result]);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  read(a[0].place.x);
  read(a[0].place.y);
  a[0].num:=0;
  a[0].time:=0;
  for i:=1 to n do
    begin
       read(a[i].place.x,a[i].place.y,a[i].time);
       a[i].num:=i;
    end;
  qsort(1,n);
  fillchar(t,sizeof(t),0);
  fillchar(from,sizeof(from),0);
  fillchar(ok,sizeof(ok),false);
  for i:=1 to n do
    for j:=0 to i-1 do
     if ((t[j]<>0)or (j=0)) and (t[i]<t[j]+1) and (dest2(a[i].place,a[j].place)<=(a[i].time-a[j].time)*(a[i].time-a[j].time)*100) then
       begin
         t[i]:=t[j]+1;
         from[i]:=j;
       end;
  l:=findmaxnum;
  while l<>0 do
    begin
      ok[a[l].num]:=true;
      l:=from[l];
    end;
  for i:=1 to n do
    if ok[i] then
     write(i,' ');
end.