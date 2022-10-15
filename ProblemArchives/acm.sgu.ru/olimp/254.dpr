{$APPTYPE CONSOLE}

uses
  Math;
var h,pr:array[1..100] of integer;
    a:array[1..100,1..100] of record
                           sim,next,pred,v:integer
                           end;
    used:array[0..100] of boolean;
    n,m,p,l,i,j:integer;
procedure delete1(var k,s:integer);
begin
  if k=h[s] then h[s]:=a[s,k].next
  else
    a[s,a[s,k].pred].next:=a[s,k].next;
  if (a[s,k].next<>n+1) then a[s,a[s,k].next].pred:=a[s,k].pred;
  k:=a[s,k].sim;
  dec(s);
end;

procedure delete(k:integer);
var i,s:integer;
begin
  used[k]:=true;
  for i:=1 to n do
    if a[m,i].v=k then
    begin
      k:=i;
      break;
    end;
  s:=m;
  while s>=1 do delete1(k,s);
end;

function viner:integer;
var kol:array of integer;
    i,k:integer;
begin
  result:=0;
  setlength(kol,n+1);
  for i:=0 to n do
  if used[i] then kol[i]:=1000 else
    kol[i]:=0;
  for i:=1 to m do
    inc(kol[a[i,h[i]].v]);
  for i:=1 to n do
    if (kol[i]>m/2) and not used[i] then result:=i;
  if result=0 then
    begin
      k:=minintvalue(kol);
      if k=1000 then
      begin
        result:=n+1;
        writeln(0);
        exit;
      end;
      for i:=1 to n do
        if kol[i]=k then delete(i);
    end
  else writeln(result);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(p);
  for l:=1 to p do
   begin
     read(n,m);
     fillchar(pr,sizeof(pr),0);
     fillchar(used,sizeof(used),false);
     fillchar(a,sizeof(a),0);
     fillchar(h,sizeof(h),1);
     for i:=1 to m do
       h[i]:=1;
     for i:=1 to m do
        for j:=1 to n do
          begin
          read(a[i,j].v);
          a[i,j].sim:=pr[a[i,j].v];
          a[i,j].next:=(j+1) mod (n+1);
          a[i,j].pred:=j-1;
          pr[a[i,j].v]:=j;
          end;
        used[0]:=true;
    while viner=0 do;
   end;
end.