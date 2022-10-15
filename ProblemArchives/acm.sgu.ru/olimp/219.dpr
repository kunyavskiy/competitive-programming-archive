{$APPTYPE CONSOLE}
{$q+}

uses
  SysUtils;

type line=record
        a,b,c:int64;
        end;
     point=record
       x,y:int64;
       end;
     tr=array[1..3] of point;
     der=array[1..6] of point;

var n,i,j:integer;
    d:der;
    tr1,tr2:tr;
    a,b:extended;
    q:boolean;

function sign(x:int64):integer;
begin
  if x>0 then result:=1;
  if x=0 then result:=0;
  if x<0 then result:=-1;
end;

function makeline(p1,p2:point):line;
begin
  result.a:=p1.y-p2.y;
  result.b:=p2.x-p1.x;
  result.c:=-result.a*p1.x-result.b*p1.y;
end;

function dest(a:line;b:point):int64;
begin
  result:=a.a*b.x+a.b*b.y+a.c;
end;

function ononeline(a,b,c:point):boolean;
begin
  result:=dest(makeline(a,b),c)=0;
end;

function trin(t1,t2:tr):boolean;
var zn1,zn2,zn3,zn4:integer;
    i,j:integer;
begin
  if ononeline(t1[1],t1[2],t1[3]) or  ononeline(t2[1],t2[2],t2[3]) then
    begin
      result:=false;
      exit;
    end;
  result:=true;
  for i:=1 to 3 do
    for j:=i+1 to 3 do
      begin
        zn1:=sign(dest(makeline(t1[i],t1[j]),t1[6-i-j]));
        zn2:=sign(dest(makeline(t1[i],t1[j]),t2[1]));
        zn3:=sign(dest(makeline(t1[i],t1[j]),t2[2]));
        zn4:=sign(dest(makeline(t1[i],t1[j]),t2[3]));
        result:=result and ((zn1=zn2) and (zn3=zn4) and (zn1=zn3));
      end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do
     begin
       for j:=1 to 6 do
       begin
         read(a,b);
        // assert((a*100=trunc(a*100)) and (b*100=trunc(b*100)));
         d[j].x:=trunc(a*1000);
         d[j].y:=trunc(b*1000);
       end;
       q:=false;
       tr1[1]:=d[1];
       tr1[2]:=d[2];
       tr1[3]:=d[3];
       tr2[1]:=d[4];
       tr2[2]:=d[5];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[2];
       tr1[3]:=d[4];
       tr2[1]:=d[3];
       tr2[2]:=d[5];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[2];
       tr1[3]:=d[5];
       tr2[1]:=d[3];
       tr2[2]:=d[4];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[2];
       tr1[3]:=d[6];
       tr2[1]:=d[3];
       tr2[2]:=d[4];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[3];
       tr1[3]:=d[4];
       tr2[1]:=d[2];
       tr2[2]:=d[5];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[3];
       tr1[3]:=d[5];
       tr2[1]:=d[2];
       tr2[2]:=d[4];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[3];
       tr1[3]:=d[6];
       tr2[1]:=d[2];
       tr2[2]:=d[4];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[4];
       tr1[3]:=d[5];
       tr2[1]:=d[2];
       tr2[2]:=d[3];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[4];
       tr1[3]:=d[6];
       tr2[1]:=d[2];
       tr2[2]:=d[3];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[1];
       tr1[2]:=d[5];
       tr1[3]:=d[6];
       tr2[1]:=d[2];
       tr2[2]:=d[3];
       tr2[3]:=d[4];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[3];
       tr1[3]:=d[4];
       tr2[1]:=d[1];
       tr2[2]:=d[5];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[3];
       tr1[3]:=d[5];
       tr2[1]:=d[1];
       tr2[2]:=d[4];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[3];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[4];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[4];
       tr1[3]:=d[5];
       tr2[1]:=d[1];
       tr2[2]:=d[3];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[4];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[3];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[2];
       tr1[2]:=d[5];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[3];
       tr2[3]:=d[4];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[3];
       tr1[2]:=d[4];
       tr1[3]:=d[5];
       tr2[1]:=d[1];
       tr2[2]:=d[2];
       tr2[3]:=d[6];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[3];
       tr1[2]:=d[4];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[2];
       tr2[3]:=d[5];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[3];
       tr1[2]:=d[5];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[2];
       tr2[3]:=d[4];
       q:=q or trin(tr1,tr2);

       tr1[1]:=d[4];
       tr1[2]:=d[5];
       tr1[3]:=d[6];
       tr2[1]:=d[1];
       tr2[2]:=d[2];
       tr2[3]:=d[3];
       q:=q or trin(tr1,tr2);
       if q then writeln('YES')
       else writeln('NO');
     end;
end.