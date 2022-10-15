{$APPTYPE CONSOLE}
{$H+}

uses
  SysUtils;

type tablelement=record
          name:string;
          t1:integer;
          t2:integer;
          t3:integer;
          t4:integer;
          next:integer;
          end;

const base=(1 shl 16)-1;

var tabl:array[1..1000] of tablelement;
    heads:array[1..base-1] of integer;
    free,n,i:integer;
    s:string;

function hash(s:string):integer;
var i:integer;
  begin
    result:=0;
    for i:=1 to length(s) do
      result:=(result*137+ord(s[i])) mod base
  end;

procedure conect(s:string; sec:integer);
var k,l:integer;
begin
  k:=hash(s);
  l:=heads[k];
  while l<>0 do
    begin
      if tabl[l].name=s then
        begin
          if tabl[l].t2=0 then tabl[l].t2:=sec
          else
            if tabl[l].t3=0 then tabl[l].t3:=sec
            else
              if tabl[l].t4=0 then tabl[l].t4:=sec
              else
                begin
                  writeln('Disconnected #',tabl[l].t1);
                  tabl[l].t1:=tabl[l].t2;
                  tabl[l].t2:=tabl[l].t3;
                  tabl[l].t3:=tabl[l].t4;
                  tabl[l].t4:=sec;
                end;
           exit;
        end;
      l:=tabl[l].next;
    end;
  tabl[free].name:=s;
  tabl[free].t1:=sec;
  tabl[free].t2:=0;
  tabl[free].t3:=0;
  tabl[free].t4:=0;
  tabl[free].next:=heads[k];
  heads[k]:=free;
  inc(free);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  free:=1;
  for i:=1 to n do
   begin
     readln(s);
     conect(s,i);
   end;
end.