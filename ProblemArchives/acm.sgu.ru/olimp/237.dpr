{$MINSTACKSIZE $16777000}
{$MAXSTACKSIZE $16777000}
{$apptype console}

uses
  SysUtils;

type node=record
      pr,l,r,sfl:integer;
      next:array['0'..'2'] of integer;
      end;

     pos=record
       ver,before:integer;
       end;

var s:string;
    tree:array[0..550000] of node;
    ktree,i,nv:integer;
    sum:int64;
    p:pos;
    c:char;

function posi(a,b:integer):pos;
begin
  result.ver:=a;
  result.before:=b;
end;

function lengthver(v:integer):int64;
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
  nv:=tree[1].next[s[1]];
  last:=nv;
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
              break;
            end;
          p:=p1;
        end;
  end;
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  s:='';
  while not seekeof do
    begin
      read(c);
      if c in ['0','1'] then   s:=s+c;
    end;
  s:=s+'2';
  ktree:=1;
  tree[0].next['0']:=1;
  tree[0].next['1']:=1;
  tree[0].next['2']:=1;
  tree[1].next['0']:=-1;
  tree[1].next['1']:=-1;
  tree[1].next['2']:=-1;
  tree[1].pr:=0;
  tree[1].l:=0;
  tree[1].sfl:=0;
  tree[1].r:=1;
  addvertex(1,1,length(s)+1);
  maketree;
  sum:=0;
  for i:=2 to ktree do
    sum:=sum+lengthver(i);
  sum:=sum-length(s);
  write(sum);
end.