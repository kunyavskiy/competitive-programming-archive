{$APPTYPE CONSOLE}

uses
  sysutils,math;

type queue=array[0..1000400] of integer;

var n,i,h1,h2,t1,t2,a,h:integer;
    q2,q1:queue;
    st:array[1..400] of integer;

procedure stpush(x:integer);
begin
 inc(h);
 st[h]:=x;
end;

function stpop:integer;
begin
 stpop:=st[h];
 dec(h)
end;

procedure push1 (x:integer);
  begin
   q1[t1]:=x;
   t1:=t1+1;
  end;

function pop1:integer;
  begin
   pop1:=q1[h1];
   q1[h1]:=0;
   h1:=h1+1;
  end;

function empty1:boolean;
 begin
 empty1:=h1=t1
 end;

procedure push2 (x:integer);
  begin
   q2[t2]:=x;
   t2:=t2+1;
  end;

function pop2:integer;
  begin
   pop2:=q2[h2];
   q2[h2]:=0;
   h2:=h2+1;
  end;

function empty2:boolean;
 begin
 empty2:=h2=t2
 end;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 t1:=0;
 t2:=0;
 h1:=0;
 h2:=0;
 h:=0;
 read(n);
 for i:=1 to n do
  begin
   read(a);
   stpush(a);
  end;
 for i:=1 to n do push1(stpop);
  for i:=1 to n do
  begin
   read(a);
   stpush(a);
  end;
  for i:=1 to n do push2(stpop);
  for i:=1 to 1000001 do
  begin
   if empty1 or empty2 then  begin write(i-1); close(input); close(output); halt; end;
   if q1[h1]>q2[h2] then begin   push1(pop1); push1(pop2); end
   else begin   push2(pop2); push2(pop1); end;
  end;
  write('TOO MANY')
end.