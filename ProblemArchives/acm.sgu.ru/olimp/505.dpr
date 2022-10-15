{$APPTYPE CONSOLE}

uses
  SysUtils;

const base=596345;
      day=3600*24;
      hour=3600;
      minute=60;

type tablel=record
          name:string;
          inclub:integer;
          next:integer;
          end;
    event=record
           name:string;
           come:boolean;
           zap:boolean;
           time:real;
           end;




var tabl:array[1..1000] of tablel;
    h:array[0..base] of integer;
    events:array[1..2000] of event;
    free,n,m,i,j,kol:integer;

function hash(s:string):integer;
var i:integer;
begin
  result:=0;
  for i:=1 to length(s) do
    result:=(result*239+ord(s[i])) mod base;
end;

function add(s:string):boolean;
var ha,l:integer;
begin
  ha:=hash(s);
  l:=h[ha];
  while l<>0 do
    begin
     if tabl[l].name=s then
       begin
         tabl[l].inclub:=1-tabl[l].inclub;
         result:=tabl[l].inclub<>0;
         exit;
       end;
     l:=tabl[l].next;
    end;
  inc(free);
  tabl[free].next:=h[ha];
  tabl[free].inclub:=1;
  tabl[free].name:=s;
  result:=true;
  h[ha]:=free;
end;

function find(s:string):integer;
var ha,l:integer;
begin
  ha:=hash(s);
  l:=h[ha];
  while l<>0 do
    begin
     if tabl[l].name=s then
       begin
         result:=l;
         exit;
       end;
     l:=tabl[l].next;
    end;
   halt(1);
end;

procedure swap(var a,b:event);
var t:event;
begin
  t:=a;
  a:=b;
  b:=t;
end;

procedure qsort(l,r:integer);
var i,j:integer;
    m:real;
begin
  i:=l;
  j:=r;
  m:=events[random(r-l+1)+l].time;
  while i<=j do
    begin
      while events[i].time<m do inc(i);
      while events[j].time>m do dec(j);
      if i<=j then
        begin
          swap(events[i],events[j]);
          inc(i);
          dec(j);
        end;
    end;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;

function readtime:integer;
var c:char;
    s:string;
begin
  result:=0;
  read(c);
  s:='';
  s:=s+c;
  read(c);
  s:=s+c;
  result:=result+hour*strtoint(s);
  read(c);
  if c<>':' then
    halt(1);
  read(c);
  s:='';
  s:=s+c;
  read(c);
  s:=s+c;
  result:=result+minute*strtoint(s);
  read(c);
  if c<>':' then
    halt(1);
  read(c);
  s:='';
  s:=s+c;
  read(c);
  s:=s+c;
  result:=result+strtoint(s);
  read(c);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do
    begin
      events[i].time:=readtime;
      readln(events[i].name);
      if (events[i].name[1]=' ') or (events[i].name[length(events[i].name)]=' ') then
        halt(1);
      events[i].come:=add(events[i].name);
      if not events[i].come then
         events[i].time:=events[i].time+0.5;
    end;
  for i:=1 to m do
    begin
      events[i+n].time:=readtime+0.25;
      readln;
      events[i+n].zap:=true;
    end;
  qsort(1,n+m);
  for i:=1 to free do
     tabl[i].inclub:=0;
  for i:=1 to n+m do
    begin
      if events[i].zap then
        begin
          kol:=0;
          for j:=1 to free do
             if tabl[j].inclub>0 then inc(kol);
          write(kol);
          for j:=1 to free do
             if tabl[j].inclub>0 then write(' ',tabl[j].name);
          writeln;
          continue;
        end;
      if events[i].come then
        inc(tabl[find(events[i].name)].inclub)
      else
        dec(tabl[find(events[i].name)].inclub);
    end;
end.