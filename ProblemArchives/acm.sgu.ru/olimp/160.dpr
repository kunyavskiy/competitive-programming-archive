{$APPTYPE CONSOLE}

uses
  SysUtils;

type borel=record
        next:array['a'..'z'] of integer;
        nextprob:boolean;
        end;

var bor:array[1..3000] of borel;
    kbor,n,i:integer;
    s1,s2,s:string;

function gooradd (v:integer;c:char):integer;
begin
  if c=' ' then
    begin
      result:=1;
      bor[v].nextprob:=true;
      exit;
    end;
  if (bor[v].next[c]=-1) then
    begin
      inc(kbor);
      fillchar(bor[kbor].next,sizeof(bor[kbor].next),-1);
      bor[kbor].nextprob:=false;
      bor[v].next[c]:=kbor;
      result:=kbor;
    end
  else
    result:=bor[v].next[c];
end;

procedure add(s:string);
var t,i:integer;
begin
  t:=1;
  for i:=1 to length(s) do
  if s[i] in ['a'..'z'] then
    t:=gooradd(t,s[i])
  else
    t:=gooradd(t,chr(ord(s[i])-ord('A')+ord('a')));
  t:=gooradd(t,' ');
end;

function go (v:integer;c:char):integer;
begin
  if c in ['A'..'Z'] then
    c:=chr(ord(c)-ord('A')+ord('a'));
  if c=' ' then
   if bor[v].nextprob then
    begin
      result:=1;
      exit;
    end
   else
     begin
       result:=-1;
       exit;
     end;
   result:=bor[v].next[c];
end;


procedure gen(s1,s2,res:string;v:integer);
begin
  if v=-1 then exit;
  if (s1='') and  (s2='') then
    if bor[v].nextprob then
      begin
        write(res);
        close(input);
        close(output);
        halt;
      end
    else
     exit;
  if length(s1)<>0 then
     gen(copy(s1,2,length(s1)-1),s2,res+s1[1],go(v,s1[1]));
  if length(s2)<>0 then
     gen(s1,copy(s2,2,length(s2)-1),res+s2[1],go(v,s2[1]));
  gen(s1,s2,res+' ',go(v,' '));
end;


begin

  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s1);
  readln(s2);
  readln(n);
  fillchar(bor[1].next,sizeof(bor[1].next),-1);
  kbor:=1;
  for i:=1 to n do
    begin
      readln(s);
      add(s);
    end;
  if bor[1].nextprob then
    begin
      write('modgmnef;lgmd');
      exit;
    end;
  gen(s1,s2,'',1);
end.