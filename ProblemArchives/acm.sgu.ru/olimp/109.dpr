{$APPTYPE CONSOLE}
{$r+,q+}

uses
  Math;

const eps=0.0000001;

type point=record
       x,y:extended;
       end;
     otr=record
       p1,p2:point;
       end;
     line=record
      a,b,c:extended;
      end;

var k,s,i,l:integer;
    per:array[1..100] of point;
    p11,p12,p13,p21,p22,p23:point;
    o12,o13,o11,o21,o22,o23:otr;

function makeline(p1,p2:point):line;
begin
  result.a:=p1.y-p2.y;
  result.b:=p2.x-p1.x;
  result.c:=-result.a*p1.x-result.b*p1.y;
end;

function makeotr(p1,p2:point):otr;
begin
   result.p1:=p1;
   result.p2:=p2;
end;

function inotr(a:point;b:otr):boolean;
var l1:line;
begin
  l1:=makeline(b.p1,b.p2);
  if l1.a*a.x+l1.b*a.y+l1.c<>0 then
    begin
      result:=false;
      exit;
    end;
  if (((l1.b=0) and (abs(a.x-b.p1.x)<eps)) or ((a.x>min(b.p1.x,b.p2.x)) and (a.x<max(b.p1.x,b.p2.x)))) and (((l1.a=0) and (abs(a.y-b.p1.y)<eps)) or ((a.y>min(b.p1.y,b.p2.y)) and (a.y<max(b.p1.y,b.p2.y)))) then
    result:=true
  else result:=false;
end;
function ravn(a,b:point):boolean;
begin
  result:=(abs(a.x-b.x)<=eps) and (abs(a.y-b.y)<=eps)
end;

procedure intersecotr(o1,o2:otr);
var l1,l2:line;
    d:extended;
    ko:integer;
    p:point;
begin
  l1:=makeline(o1.p1,o1.p2);
  l2:=makeline(o2.p1,o2.p2);
  d:=-l1.a*l2.b+l1.b*l2.a;
  if d=0 then
    begin
      ko:=0;
      if inotr(o1.p1,o2) then inc(ko);
      if inotr(o1.p2,o2) then inc(ko);
      if inotr(o2.p1,o1) then inc(ko);
      if inotr(o2.p2,o1) then inc(ko);
      if ko>=2 then
        begin
          write(-1);
          close(input);
          close(output);
          halt;
        end;
      if inotr(o1.p1,o2) and (ravn(o1.p2,o2.p1) or (ravn(o1.p2,o2.p2))) then
         begin
          write(-1);
          close(input);
          close(output);
          halt;
         end;
      if inotr(o1.p2,o2)and (ravn(o1.p1,o2.p1) or (ravn(o1.p1,o2.p2))) then
         begin
          write(-1);
          close(input);
          close(output);
          halt;
         end;
      if inotr(o2.p1,o1) and ((ravn(o2.p2,o1.p1)) or (ravn(o2.p2,o1.p2))) then
         begin
          write(-1);
          close(input);
          close(output);
          halt;
         end;
      if inotr(o2.p2,o1) and (ravn(o2.p1,o1.p1) or ravn(o2.p1,o1.p2))then
         begin
          write(-1);
          close(input);
          close(output);
          halt;
         end;
      exit;
    end;
  p.y:=(l1.a*l2.c-l1.c*l2.a)/d;
  p.x:=(l1.c*l2.b-l1.b*l2.c)/d;
  if inotr(p,o1) and inotr(p,o2) then
    begin
      inc(k);
      per[k]:=p;
    end;
end;



function ravnotr(a,b:otr):boolean;
begin
  result:=ravn(a.p1,b.p1) and ravn(a.p2,b.p2);
  result:=result or (ravn(a.p1,b.p2) and ravn(a.p2,b.p1));
end;

function more(a,b:point):boolean;
begin
  result:=a.x-b.x>eps;
  result:=result or ((abs(a.x-b.x)<eps) and (a.y-b.y>eps));
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m,t:point;
begin
  m:=per[random(r-l+1)+l];
  i:=l; j:=r;
  repeat
    while more(m,per[i]) do inc(i);
    while more(per[j],m) do dec(j);
    if i<=j then
    begin
      t:=per[i]; per[i]:=per[j]; per[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if j>l then qsort(l,j);
  if i<r then qsort(i,r);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(p11.x,p11.y);
  read(p12.x,p12.y);
  read(p13.x,p13.y);
  read(p21.x,p21.y);
  read(p22.x,p22.y);
  read(p23.x,p23.y);
  o11:=makeotr(p11,p12);
  o12:=makeotr(p12,p13);
  o13:=makeotr(p13,p11);
  o21:=makeotr(p21,p22);
  o22:=makeotr(p22,p23);
  o23:=makeotr(p23,p21);
  k:=0;
  if inotr(p11,o21) or inotr(p11,o22) or inotr(p11,o23) then
    begin
      inc(k);
      per[k]:=p11;
    end;
  if inotr(p12,o21) or inotr(p12,o22) or inotr(p12,o23) then
    begin
      inc(k);
      per[k]:=p12;
    end;
  if inotr(p13,o21) or inotr(p13,o22) or inotr(p13,o23) then
    begin
      inc(k);
      per[k]:=p13;
    end;

 if inotr(p21,o11) or inotr(p21,o12) or inotr(p21,o13) then
    begin
      inc(k);
      per[k]:=p21;
    end;
  if inotr(p22,o11) or inotr(p22,o12) or inotr(p22,o13) then
    begin
      inc(k);
      per[k]:=p22;
    end;
  if inotr(p23,o11) or inotr(p23,o12) or inotr(p23,o13) then
    begin
      inc(k);
      per[k]:=p23;
    end;
  if ravn(p11,p21) or ravn(p11,p22) or ravn(p11,p23) then
    begin
      inc(k);
      per[k]:=p11;
    end;
  if ravn(p11,p21) or ravn(p11,p22) or ravn(p11,p23) then
    begin
      inc(k);
      per[k]:=p11;
    end;
  if ravn(p12,p21) or ravn(p12,p22) or ravn(p12,p23) then
    begin
      inc(k);
      per[k]:=p12;
    end;
  if ravn(p13,p21) or ravn(p13,p22) or ravn(p13,p23) then
    begin
      inc(k);
      per[k]:=p13;
    end;
  if ravnotr(o11,o21) or ravnotr(o11,o22) or ravnotr(o11,o23) then
    begin
      write(-1);
      close(input);
      close(output);
      halt;
    end;
  if ravnotr(o12,o21) or ravnotr(o12,o22) or ravnotr(o12,o23) then
    begin
      write(-1);
      close(input);
      close(output);
      halt;
    end;
  if ravnotr(o12,o21) or ravnotr(o12,o22) or ravnotr(o12,o23) then
    begin
      write(-1);
      close(input);
      close(output);
      halt;
    end;
  intersecotr(o11,o21);
  intersecotr(o11,o22);
  intersecotr(o11,o23);
  intersecotr(o12,o21);
  intersecotr(o12,o22);
  intersecotr(o12,o23);
  intersecotr(o13,o21);
  intersecotr(o13,o22);
  intersecotr(o13,o23);
  if k>0 then qsort(1,k);
  if k>0 then s:=1
  else
    begin
      write(0);
      exit;
    end;
  l:=1;
  for i:=2 to k do
    if not ravn(per[i],per[l]) then
      begin
        inc(s);
        l:=i;
      end;
  if s<10 then
    write(s)
  else write(-1);
end.