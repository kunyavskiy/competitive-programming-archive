{$APPTYPE CONSOLE}

uses
  SysUtils;

type tablel=record
       next:integer;
       v:string;
     end;
     reb=record
       next:integer;
       v:integer;
       end;

const base=54397;

var names:array[1..5000] of tablel;
    headtabl:array[0..base] of integer;
    h:array[1..5000] of integer;
    g:array[1..5000] of reb;
    freenames,freeg,n,m,i,t1,t2,kol,st,j:integer;
    used:array[1..5000] of boolean;
    c:char;
    s,s1:string;

procedure dfs(v,p:integer);
var l:integer;
begin
   used[v]:=true;
   l:=h[v];
   while l<>0 do
     begin
       if used[g[l].v] then
        begin
         if g[l].v<>p then
           begin
             t1:=st;
             t2:=g[l].v;
           end;
        end
       else
         dfs(g[l].v,v);
       l:=g[l].next;
     end;
end;

procedure addgraf(a,b:integer);
begin
  inc(freeg);
  g[freeg].next:=h[a];
  g[freeg].v:=b;
  h[a]:=freeg;
  inc(freeg);
  g[freeg].next:=h[b];
  g[freeg].v:=a;
  h[b]:=freeg;
end;

function hash(s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
   result:=(result*37 +ord(s[i])) mod base;
end;

function addtabl(s:string;h:integer):integer;
begin
  inc(freenames);
  result:=freenames;
  names[freenames].v:=s;
  names[freenames].next:=headtabl[h];
  headtabl[h]:=freenames;
end;

function namenum(s:string):integer;
var h,l:integer;
begin
  h:=hash(s);
  l:=headtabl[h];
  while l<>0 do
    begin
      if names[l].v=s then
        begin
          result:=l;
          exit;
        end;
      l:=g[l].next
    end;
  result:=addtabl(s,h);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to m do
    begin
      read(c);
      s:='';
      s1:='';
      while c<>' ' do
        begin
          s:=s+c;
          read(c);
        end;
     readln(s1);
     for j:=1 to length(s1) do
     assert(s1[i] in ['A'..'Z'],'error in tre test');
     for j:=1 to length(s) do
     assert(s[i] in ['A'..'Z'],'error in tre test');
      addgraf(namenum(s),namenum(s1));
    end;
  kol:=-1;
  for i:=1 to n do
    if not used[i] then
      begin
        st:=i;
        inc(kol);
        dfs(i,0);
      end;
  if kol=0 then writeln('Yes')
  else
    begin
      writeln('No');
      writeln(kol);
    end;
  if t1=0 then  writeln('Yes')
  else
    begin
      writeln('No');
      writeln(names[t1].v,' ',names[t2].v);
    end;
end.