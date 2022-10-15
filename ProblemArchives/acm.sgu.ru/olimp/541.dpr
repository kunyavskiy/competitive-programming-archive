{$APPTYPE CONSOLE}

uses
  SysUtils;



type treeel=record
       x:string;
       val:string;
       y:integer;
       l,r:integer;
       end;

var tree:array[1..10000] of treeel;
    ktree,head:integer;
    tecsec,s,newkee,newval:string;
    

function newel(var kee,val:string):integer;
begin
  inc(ktree);
  tree[ktree].x:=kee;
  tree[ktree].val:=val;
  tree[ktree].y:=random(15351623);
  tree[ktree].l:=-1;
  tree[ktree].r:=-1;
  result:=ktree;
end;

function merge(var l,r:integer):integer;
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
  if tree[l].y>tree[r].y then
    begin
       result:=l;
       tree[l].r:=merge(tree[l].r,r);
       exit;
    end;
       result:=r;
       tree[r].l:=merge(l,tree[r].l);
end;

procedure split (var v,l,r:integer;x:string);
begin
   if v=-1 then
     begin
       l:=-1;
       r:=-1;
       exit;
     end;
   if tree[v].x<=x then
      begin
        l:=v;
        split(tree[v].r,tree[v].r,r,x);
        exit;
      end;
   r:=v;
   split(tree[v].l,l,tree[v].l,x);
end;

procedure norm(var s,kee,val:string);
var i:integer;
begin
  while (length(s)<>0) and (s[1]=' ') do
     delete(s,1,1);
  if length(s)=0 then
    begin
      kee:='';
      exit;
    end;
  if s[1]=';' then
    begin
      kee:='';
      exit;
    end;
  while s[length(s)]=' ' do
    delete(s,length(s),1);
  if s[1]='[' then
    begin
     while s[2]=' ' do
       delete(s,2,1);
     while s[length(s)-1]=' ' do
       delete(s,length(s)-1,1);
     insert(chr(1),s,length(s));
     kee:=s;
     tecsec:=s;
     exit;
    end;
  i:=1;
  kee:='';
  while s[i] in ['a'..'z','A'..'Z','0'..'9','.','-'] do
    begin
     kee:=kee+s[i];
     inc(i);
    end;
  kee:=tecsec+kee;
  val:='';
  while not (s[i] in ['a'..'z','A'..'Z','0'..'9','.','-']) do
    inc(i);
  while (i<=length(s)) and  (s[i] in ['a'..'z','A'..'Z','0'..'9','.','-']) do
    begin
     val:=val+s[i];
     inc(i);
    end; 
end;

function find(kee:string):integer;
var t:integer;
begin
  t:=head;
  while (tree[t].x<>kee) and (t<>-1) do
    if tree[t].x<kee then
      t:=tree[t].r
    else
      t:=tree[t].l;
  result:=t;
end;

procedure add(newkee,newval:string);
var k,l,r,m:integer;
begin
  k:=find(newkee);
  if k=-1 then
    begin
      split(head,l,r,newkee);
      m:=newel(newkee,newval);
      head:=merge(l,m);
      head:=merge(head,r);
    end;
  tree[k].val:=newval;
end;

function getsec(var s:string):string;
var sec:string;
begin
  sec:='[';
  delete(s,1,1);
  while s[1]<>']' do
    begin
      sec:=sec+s[1];
      delete(s,1,1);
    end;
  sec:=sec+']';
  delete(s,1,1);
  result:=sec;
end;

procedure print(v:integer);
var sec:string;
begin
  if v=-1 then
    exit;
  print(tree[v].l);
  sec:=getsec(tree[v].x);
  if sec<>tecsec then
    begin
      write(copy(sec,1,length(sec)-2));
      writeln(']');
      tecsec:=sec;
    end
  else
  writeln(tree[v].x,'=',tree[v].val);
  print(tree[v].r);
end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  tecsec:='['+chr(1)+']';
  head:=-1;
  while not eof do
    begin
      readln(s);
      norm(s,newkee,newval);
      if (newkee<>'') then
        add(newkee,newval);
    end;
  tecsec:='['+chr(1)+']';
  print(head);  
end.
