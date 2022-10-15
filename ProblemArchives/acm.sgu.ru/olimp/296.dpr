{$apptype console}
{$O+}

uses
  Math;
const maxlen=100000;

type state=record
      length,link:integer;
      next:array['A'..'Z'] of integer;
      end;
var st:array[0..maxlen*2] of state;
    sz,last,i:integer;
    s:string;

procedure init;
begin
  st[0].length:=0;
  st[0].link:=-1;
  fillchar(st[0].next,sizeof(st[0].next),-1);
  sz:=1;
end;

procedure sa_extend(c:char);
var nlast,p,q,clone:integer;
begin
  nlast:=sz;
  inc(sz);
	st[nlast].length:=st[last].length+1;
  fillchar(st[nlast].next,sizeof(st[nlast].next),-1);
  p:=last;
  while (p<>-1) and (st[p].next[c]=-1) do
   begin
     st[p].next[c]:= nlast;
     p:=st[p].link;
   end;
   if p=-1 then
     st[nlast].link:=0
   else
     begin
		   q:=st[p].next[c];
		   if st[p].length+1=st[q].length then
			    st[nlast].link:=q
		    else
        begin
			  clone:=sz;
        inc(sz);
			  st[clone].length:=st[p].length+1;
        st[clone].next:=st[q].next;
			 st[clone].link:=st[q].link;
			while (p<>-1) and (st[p].next[c]=q) do
        begin
        st[p].next[c]:=clone;
    		p:=st[p].link;
       end;
			st[q].link:=clone;
      st[nlast].link:=clone;
	      end;
	   end;
	last:=nlast;
end;

function exist(s:string):boolean;
var t,i:integer;
begin
  result:=false;
  t:=0;
  for i:=1 to length(s) do
   begin
    t:=st[t].next[s[i]];
    if t=-1 then exit;
   end;
  result:=true;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  init;
  while not seekeof do
    begin
      readln(s);
      if s[1]='A' then
        begin
          delete(s,1,2);
          for i:=1 to length(s) do
            if s[i] in ['a'..'z'] then
               s[i]:=chr(ord(s[i])-ord('a')+ord('A'));
          for i:=1 to length(s) do
             sa_extend(s[i]);
        end;
      if s[1]='?' then
        begin
          delete(s,1,2);
          for i:=1 to length(s) do
            if s[i] in ['a'..'z'] then
               s[i]:=chr(ord(s[i])-ord('a')+ord('A'));
          if exist(s) then writeln('YES')
          else writeln('NO');
        end;
    end;
end.