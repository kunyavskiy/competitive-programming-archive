{$APPTYPE CONSOLE}
{$r+,q+}

uses
  SysUtils;

type treeel=record
        sum,kol:int64;
        end;
     event=record
        come:boolean;
        num:int64;
        per:int64;
        end;
     person=record
        add:int64;
        oldnum:integer;
        end;


var tree:array[1..1000000] of treeel;
    list,n,m,p,i,a,b,c,d,ep:integer;
    newnum:array[1..500000] of integer;
    persons:array[1..500000] of person;
    events:array[1..500000] of event;
    res:int64;

function kth(k:integer):integer;
begin
  if tree[1].kol<k then
    begin
       result:=n;
       exit;
    end;
  result:=1;
  while result<list do
     begin
        if tree[2*result].kol>=k then result:=2*result
        else
          begin
             k:=k-tree[2*result].kol;
             result:=2*result+1;
          end;
     end;
  result:=result-list+1;
end;

function rsq(l,r:int64):int64;
begin
   l:=list+l-1;
   r:=list+r-1;
   result:=0;
   while l<=r do
     begin
       if (l and 1)=1 then result:=result+tree[l].sum;
       if (r and 1)=0 then result:=result+tree[r].sum;
       l:=(l+1) shr 1;
       r:=(r-1) shr 1;
     end;
end;

procedure update(a:event);
var k:integer;
begin
  a.per:=newnum[a.per];
  if a.come then
    begin
      k:=a.per+list-1;
      tree[k].sum:=persons[a.per].add;
      tree[k].kol:=1;
      while k>1 do
        begin
          k:=k div 2;
          tree[k].sum:=tree[2*k].sum+tree[2*k+1].sum;
          tree[k].kol:=tree[2*k].kol+tree[2*k+1].kol;
        end;
    end
  else
    begin
      k:=a.per+list-1;
      tree[k].sum:=0;
      tree[k].kol:=0;
      while k>1 do
        begin
          k:=k div 2;
          tree[k].sum:=tree[2*k].sum+tree[2*k+1].sum;
          tree[k].kol:=tree[2*k].kol+tree[2*k+1].kol;
        end;
    end;
end;

procedure swapevent(var a,b:event);
var t:event;
begin
   t:=a;
   a:=b;
   b:=t;
end;

procedure qsortevent(l,r:integer);
var m,i,j:integer;
begin
  m:=events[random(r-l+1)+l].num;
  i:=l;
  j:=r;
  while i<=j do
    begin
      while events[i].num<m do inc(i);
      while events[j].num>m do dec(j);
      if i<=j then
        begin
          swapevent(events[i],events[j]);
          inc(i);
          dec(j);
        end;
    end;
  if l<j then qsortevent(l,j);
  if i<r then qsortevent(i,r);
end;



procedure swapper(var a,b:person);
var t:person;
begin
   t:=a;
   a:=b;
   b:=t;
end;

procedure qsortper(l,r:integer);
var m,i,j:integer;
begin
  m:=persons[random(r-l+1)+l].add;
  i:=l;
  j:=r;
  while i<=j do
    begin
      while persons[i].add>m do inc(i);
      while persons[j].add<m do dec(j);
      if i<=j then
        begin
          swapper(persons[i],persons[j]);
          inc(i);
          dec(j);
        end;
    end;
  if l<j then qsortper(l,j);
  if i<r then qsortper(i,r);
end;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(n,m,p);
   res:=0;
   for i:=1 to n do
     begin
       read(a,b,c,d);
       res:=res+b*(d-c);
       persons[i].add:=a-b;
       if persons[i].add<0 then
          persons[i].add:=0;
       events[2*i-1].come:=true;
       events[2*i-1].num:=c;
       events[2*i-1].per:=i;
       events[2*i].come:=false;
       events[2*i].num:=d;
       events[2*i].per:=i;
       persons[i].oldnum:=i;
     end;
   qsortper(1,n);
   for i:=1 to n do
     newnum[persons[i].oldnum]:=i;
   list:=1;
   while list<n do
     list:=list*2;
   qsortevent(1,2*n);
   ep:=1;
   for i:=1 to p do
     begin
       while (ep<=2*n) and (events[ep].num=i) do
         begin
           update(events[ep]);
           inc(ep);
         end;
       res:=res+rsq(1,kth(m));
     end;
   write(res);
end.