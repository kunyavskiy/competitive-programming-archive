{$APPTYPE CONSOLE}
{$r+,q+}


type ocno=record
       left,right,down,up:integer;
       end;

var g:array['0'..'z','0'..'z'] of boolean;
    used:array['0'..'z'] of boolean;
    ecran:array['0'..'z'] of ocno;
    a:array[1..100,1..100] of char;
    n,m,i,j:integer;
    c:char;
function inocn(a:ocno;x,y:integer):boolean;
var ql,qr,qd,qu,qlr,qud:boolean;
begin
  if a.left=-1 then
    begin
      result:=false;
      exit;
    end;
  ql:=y=a.left;
  qr:=y=a.right;
  qd:=x=a.down;
  qu:=x=a.up;
  qud:=(x<=a.down) and (x>=a.up);
  qlr:=(y>=a.left) and (y<=a.right);
  result:=((ql or qr) and qud) or ((qu or qd) and qlr);
end;

function min(a,b:integer):integer;
begin
 result:=0;
 if (a=-1) then result:=b;
 if b=-1 then result:=a;
 if result=0 then
   if a<b then result:=a
   else result:=b;
end;
function max(a,b:integer):integer;
begin
 result:=0;
 if (a=-1) then result:=b;
 if b=-1 then result:=a;
 if result=0 then
   if a>b then result:=a
   else result:=b;
end;
procedure dfs(v:char);
var i:char;
begin
  used[v]:=true;
  for i:='0' to 'z' do
    if g[v,i] and (not used[i]) then
       dfs(i);
  write(v);
end;

procedure topsort;
var i:char;
begin
  for i:='0' to 'z' do
    if (ecran[i].left<>-1) and (not used[i]) then dfs(i);
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(m,n);
  fillchar(ecran,sizeof(ecran),-1);
  for i:=1 to n do
   begin
    for j:=1 to m do
      begin
        read(c);
        if c in  ['0'..'9','A'..'Z','a'..'z']  then
          begin
            ecran[c].left:=min(ecran[c].left,j);
            ecran[c].right:=max(ecran[c].right,j);
            ecran[c].down:=max(ecran[c].down,i);
            ecran[c].up:=min(ecran[c].up,i);
          end;
          a[i,j]:=c;
      end;
    readln;
   end;
  for i:=1 to n do
    for j:=1 to m do
      if a[i,j] in ['0'..'9','A'..'Z','a'..'z']  then
        for c:='0' to 'z' do
          if (c<>a[i,j]) and inocn(ecran[c],i,j) then
            g[a[i,j],c]:=true;
  topsort;
end.