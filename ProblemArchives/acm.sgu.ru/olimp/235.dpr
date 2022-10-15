{$APPTYPE CONSOLE}
{$R+,Q+}

uses
  SysUtils;

type node=record
      pr,l,r,sfl,kol:integer;
      next:array['0'..'2'] of integer;
      used:boolean;
      end;

     pos=record
       ver,before:integer;
       end;

var s,s1:string;
    tree:array[-1..100000] of node;
    ktree,i,nv,k:integer;
    p:pos;

function posi(a,b:integer):pos;
begin
  result.ver:=a;
  result.before:=b;
end;

function lengthver(v:integer):integer;
begin
  result:=tree[v].r-tree[v].l;
end;


function go(v:pos; l:integer):pos;
var nv:integer;
begin
  if v.before=0 then
   begin
     nv:=tree[v.ver].next[s[l]];
     if nv=-1 then result:=posi(-1,-1)
     else result:=posi(nv,lengthver(nv)-1);
   end
  else
   begin
     if s[tree[v.ver].r-v.before]=s[l] then
        result:=posi(v.ver,v.before-1)
     else result:=posi(-1,-1);
   end;
end;

function addvertex(par,l,r:integer):integer;
var res:integer;
begin
  inc(ktree);
  res:=ktree;
  fillchar(tree[res].next,sizeof(tree[res].next),-1);
  tree[res].l:=l;
  tree[res].r:=r;
  tree[res].pr:=par;
  tree[par].next[s[l]]:=res;
  tree[res].sfl:=-1;
  result:=res;
end;

function split(p:pos):integer;
var nv,v,par:integer;
begin
  if p.before=0 then
    begin
      result:=p.ver;
      exit;
    end;
  v:=p.ver;
  par:=tree[v].pr;
  nv:=addvertex(par,tree[v].l,tree[v].r-p.before);
  tree[v].l:=tree[nv].r;
  tree[v].pr:=nv;
  tree[nv].next[s[tree[v].l]]:=v;
  result:=nv;
end;

function fastscan(v,l,r:integer):pos;
var nv:integer;
begin
  while true do
    begin
      nv:=tree[v].next[s[l]];
        if lengthver(nv)<r-l then
        begin
        l:=l+lengthver(nv);
        v:=nv;
        end
      else
       begin
         result:=posi(nv,lengthver(nv)-r+l);
         exit;
       end;
      end;
  result:=posi(nv,lengthver(nv)-r+l);
end;

function link(v:integer):integer;
var p:pos;
begin
  if tree[v].sfl<>-1then
    result:=tree[v].sfl
  else
   begin
     p:=fastscan(link(tree[v].pr),tree[v].l,tree[v].r);
     result:=split(p);
     tree[v].sfl:=result;
   end;
end;

{function create (v,l,r:integer):pos;
var cur,nv:pos;
    i,a,x:integer;
begin
  cur:=posi(v,r-l);
  for i:=l to r-1 do
   begin
     nv:=go(cur,l);
     if nv.ver=-1 then
     begin
       a:=split(cur);
       x:=addvertex(a,l,r);
       result:=posi(x,0);
       exit;
     end;
   end;
end;}

procedure maketree;
var head,last,i,nv,j:integer;
    p,p1:pos;
begin
   s:=s+'2';
   ktree:=1;
   tree[0].next['0']:=1;
   tree[0].next['1']:=1;
   tree[0].next['2']:=1;
   fillchar(tree[1].next,sizeof(tree[1].next),-1);
   tree[1].pr:=0;
   tree[1].l:=0;
   tree[1].sfl:=0;
   tree[1].r:=1;
   addvertex(1,1,length(s)+1);
   last:=tree[1].next[s[1]];
   head:=1;
   for i:=2 to length(s) do
     begin
       head:=link(head);
       p:=posi(head,0);
       for j:=tree[last].l to tree[last].r-1 do
         begin
           p1:=go(p,j);
           if p1.ver=-1 then
             begin
               head:=split(p);
               last:=addvertex(head,j,tree[last].r);
               break
             end;
           p:=p1;
         end;
     end;
end;

function goc(v:pos; l:char):pos;
var nv:integer;
begin
  if v.before=0 then
   begin
     nv:=tree[v.ver].next[l];
     if nv=-1 then result:=posi(-1,-1)
     else result:=posi(nv,lengthver(nv)-1);
   end
  else
   begin
     if s[tree[v.ver].r-v.before]=l then
        result:=posi(v.ver,v.before-1)
     else result:=posi(-1,-1);
   end;
end;


procedure mark;
var p,p1:pos;
    l,par,i:integer;
begin
  p:=posi(1,0);
  l:=length(s1)+1;
  for i:=1 to length(s1) do
    begin
      p1:=goc(p,s1[i]);
      if p1.before=0 then
         tree[p1.ver].used:=true;
      if p1.ver=-1 then
         begin
           nv:=split(p);
           tree[nv].used:=true;
           l:=i;
           break;
         end;
      p:=p1;
    end;
  if l=length(s1)+1 then
  begin
    nv:=split(p);
    tree[nv].used:=true;
  end;
  for i:=2 to length(s1) do
    begin
       p:=posi(link(nv),0);
       while (l<=length(s1)) do
         begin
           p1:=goc(p,s1[l]);
           if p1.ver<>-1 then
              inc(l)
           else
             break;
         {  if p1.before=0 then
             tree[p1.ver].used:=true;}
           p:=p1;
         end;
       nv:=split(p);
       tree[nv].used:=true;
       par:=nv;
       while not tree[par].used do
         begin
           tree[par].used:=true;
           par:=tree[par].pr;
         end;
    end;
end;

function dfs(v:integer):integer;
begin
  if v=-1 then
    begin
      result:=0;
      exit;
    end;
  tree[v].kol:=lengthver(v)+dfs(tree[v].next['0'])+dfs(tree[v].next['1']);
  result:=tree[v].kol;
end;

procedure generate(v,k:integer);
var nv0,nv1,l,i:integer;
begin
  if k=0 then
  begin
    close(input);
    close(output);
    halt(0);
  end;
  nv0:=tree[v].next['0'];
  nv1:=tree[v].next['1'];
  if (k<=tree[nv0].kol) then
    begin
      l:=tree[nv0].l;
      for i:=1 to lengthver(nv0) do
        begin
          if k=0 then break;
          write(s[l]);
          inc(l);
          dec(k);
        end;
      generate(nv0,k);
    end;
  k:=k-tree[nv0].kol;
  l:=tree[nv1].l;
  for i:=1 to lengthver(nv1) do
     begin
       if k=0 then break;
       write(s[l]);
       inc(l);
       dec(k);
     end;
  generate(nv1,k);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
 { for i:=2 to length(s) do
    begin
      p:=go(p,i);
      if p.ver=-1 then
        begin
          p:=posi(2,length(s)-i+1);
          nv:=split(p);
          addvertex(nv,i,length(s));
        end;
    end;}
  maketree;
 { for i:=1 to ktree do
    sum:=sum+lengthver(i);
  sum:=sum-length(s);
  write(sum);}
  readln(s1);
  tree[1].used:=true;
  mark;
  for i:=1 to ktree do
    if not tree[i].used then
      tree[tree[i].pr].next[s[tree[i].l]]:=-1;
  read(k);
  tree[-1].kol:=0;
  if dfs(1)<k  then {halt(1)};
  generate(1,k);
end.