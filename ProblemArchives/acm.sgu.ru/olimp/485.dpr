{$r-,q-}
uses
  Math;

type   maskar=array[1..3125] of integer;
       point=record
          x:integer;
          t:byte;
          pr:integer;
        end;
       treeel=record
          y:integer;
          l,r:integer;
          mask:integer;
          end;
var pointsx:array[1..300000] of point;
    pointsy:array[1..300000] of point;
    priam:array[1..100000] of maskar;
    tree:array[-1..100000] of treeel;
    n,m,i,l,r,x1,x2,y1,y2,head,size,num,j,c:integer;
    maskin,maskout:maskar;

function newtree(v,x:integer):integer;
begin
  if v=-1 then result:=0
  else
  begin
    result:=newtree(tree[v].l,x) or  priam[v,x] or newtree(tree[v].r,x);
    tree[v].mask:=result;
  end;
end;

function maskand(a,b:maskar):maskar;
var i:integer;
begin
  for i:=1 to size do
     result[i]:=a[i] and b[i];
end;

function merge(l,r,x:integer):integer;
begin
  if l=-1 then
    begin
      result:=r;
      exit;
    end;
  if r=-1 then
    begin
      result:=l;
      exit;
    end;
  if tree[l].y<tree[r].y then
    begin
      tree[r].l:=merge(l,tree[r].l,x);
      tree[r].mask:=tree[tree[r].l].mask or priam[r][x] or tree[tree[r].r].mask;
      result:=r;
      exit;
    end;
  tree[l].r:=merge(tree[l].r,r,x);
  tree[l].mask:=tree[tree[r].l].mask or priam[l][x] or tree[tree[r].r].mask;
  result:=l;
end;

function inmask(mask,bit:integer):boolean;
begin
  result:=(mask and (1 shl (bit-1)))<>0;
end;

procedure find(var v:integer;x,y:integer);
begin
   if  inmask(tree[tree[v].r].mask,y) then
   begin
     find(tree[v].r,x,y);
     tree[v].mask:=tree[tree[v].r].mask or tree[tree[v].l].mask or priam[v][x];
     exit;
   end;
   if  inmask(priam[v][x],y) then
     begin
        write(v,' ');
        c:=v;
        v:=merge(tree[v].l,tree[v].r,x);
        tree[c].l:=-1;
        tree[c].r:=-1;
        tree[c].y:=random(561234);
        tree[c].mask:=priam[c][x];
        exit;
     end;
  find(tree[v].l,x,y);
  tree[v].mask:=tree[tree[v].r].mask or tree[tree[v].l].mask or priam[v][x];
end;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure swappoint(var a,b:point);
var t:point;
begin
  t:=a;
  a:=b;
  b:=t;
end;



procedure qsortx(l,r:integer);
var m,i,j:integer;
begin
  m:=pointsx[random(r-l+1)+l].x;
  i:=l;
  j:=r;
  while i<=j do
    begin
      while pointsx[i].x<m do inc(i);
      while pointsx[j].x>m do dec(j);
      if i<=j then
        begin
           swappoint(pointsx[i],pointsx[j]);
           inc(i);
           dec(j);
        end;
    end;
  if l<j then qsortx(l,j);
  if i<r then qsortx(i,r);
end;

procedure qsorty(l,r:integer);
var m,i,j:integer;
begin
  m:=pointsy[random(r-l+1)+l].x;
  i:=l;
  j:=r;
  while i<=j do
    begin
      while pointsy[i].x<m do inc(i);
      while pointsy[j].x>m do dec(j);
      if i<=j then
        begin
           swappoint(pointsy[i],pointsy[j]);
           inc(i);
           dec(j);
        end;
    end;
  if l<j then qsorty(l,j);
  if i<r then qsorty(i,r);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  randomize;
  read(n);
  for i:=1 to n do
    begin
      read(x1,y1,x2,y2);
      l:=2*i-1;
      r:=2*i;
      pointsx[l].x:=min(x1,x2);
      pointsx[r].x:=max(x1,x2);
      pointsx[r].t:=2;
      pointsx[l].t:=1;
      pointsx[l].pr:=i;
      pointsx[r].pr:=i;
      pointsy[l].x:=min(y1,y2);
      pointsy[r].x:=max(y1,y2);
      pointsy[r].t:=2;
      pointsy[l].t:=1;
      pointsy[l].pr:=i;
      pointsy[r].pr:=i;
      tree[i].y:=random(561234);
      tree[i].l:=-1;
      tree[i].r:=-1;
    end;
  read(m);
  for i:=1 to m do
    begin
      l:=2*n+i;
      read(x1,y1);
      pointsx[l].x:=x1;
      pointsy[l].x:=y1;
      pointsx[l].t:=0; 
      pointsy[l].t:=0;
      pointsx[l].pr:=i;
      pointsy[l].pr:=i;
    end;
  qsortx(1,2*n+m);
  qsorty(1,2*n+m);
  fillchar(maskout,sizeof(maskout),-1);
  size:=(m shr 5)+1;
  for i:=2*n+m downto 1 do
    begin
      if pointsx[i].t=0 then
        begin
           num:=pointsx[i].pr;
           x1:=((num-1) shr 5) +1;
           y1:=1 shl ((num-1) and 31);
           maskin[x1]:=maskin[x1] xor y1;
           maskout[x1]:=maskout[x1] xor y1;
        end;
      if pointsx[i].t=1 then
        begin
          num:=pointsx[i].pr;
         priam[num]:=maskand(priam[num],maskin);
        end;
      if pointsx[i].t=2 then
         begin
            num:=pointsx[i].pr;
            priam[num]:=maskout;
         end;
    end;
  fillchar(maskout,sizeof(maskout),-1);
  fillchar(maskin,sizeof(maskin),0);
  for i:=2*n+m downto 1 do
    begin
      if pointsy[i].t=0 then
        begin
           num:=pointsy[i].pr;
           x1:=((num-1) shr 5) +1;
           y1:=1 shl ((num-1) and 31);
           maskin[x1]:=maskin[x1] xor y1;
           maskout[x1]:=maskout[x1] xor y1;
        end;
      if pointsy[i].t=1 then
        begin
            num:=pointsy[i].pr;
            priam[num]:=maskand(priam[num],maskin);
        end;
      if pointsy[i].t=2 then
         begin
            num:=pointsy[i].pr;
            priam[num]:=maskand(priam[num],maskout);
         end;
    end;
  head:=-1;
  for i:=1 to n do
      head:=merge(head,i,1);
  newtree(head,1);
  for i:=1 to size-1 do
    begin
      for j:=0 to 31 do
        if inmask(tree[head].mask,j) then
          begin
            find(head,i,j);
            head:=merge(head,c,i);
          end
        else write('0 ');
      newtree(head,i+1);
    end;
  for i:=1 to (m and 31) do
        if inmask(tree[head].mask,i) then
         begin
          find(head,size,i);
          head:=merge(head,c,size);
         end
        else write('0 ');
end.