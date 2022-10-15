{$APPTYPE CONSOLE}
{$R+,q+,o-}

uses
  Math;

const enter=chr(13)+chr(10);

var s,s1:string;
    stack:array[1..10000] of integer;
    i,h,k:integer;
    c:char;

procedure push(x:integer);
begin
  inc(h);
  stack[h]:=x;
end;

function pop:integer;
begin
  result:=stack[h];
  dec(h);
end;

procedure usebr(pos:integer);
begin
  delete(s,pos,4);
  insert(enter,s,pos);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not eof do
    begin
       readln(s1);
       s:=s+s1;
    end;
  i:=1;
  while i<=length(s)-3 do
    if copy(s,i,4)='<BR>' then
      usebr(i)
    else inc(i);
  i:=1;
  h:=0;
  while i<=length(s) do
     begin
        if s[i]='<' then
            push(i);
        if s[i]='>' then
            if h>0 then
              begin
                k:=pop;
                delete(s,k,i-k+1);
                i:=k-1;
              end;
        inc(i);
     end;
  write(s); 
end.