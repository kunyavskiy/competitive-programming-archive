{$APPTYPE CONSOLE}
{$r+,q+}


type abcd=record  equal,less:word end;
var st:array[1..40001] of word;
    a:array[1..40001] of word;
    t:array[1..40001] of abcd;
    h,n,i,temp,best,k,k1:integer;

function min(a,b:integer):integer;
begin
  if a<b then result:=a
  else result:=b;
end;

function max(a,b:integer):integer;
begin
  if a>b then result:=a
  else result:=b;
end;

procedure push(x:integer);
begin
  inc(h);
  st[h]:=x;
end;

function pop:integer;
begin
  result:=st[h];
  dec(h);
end;

procedure podschet;
var i,temp:integer;
begin
  push(n+1);
  for i:=n downto 1 do
    begin
      t[i].equal:=i;
       while true do
         begin
           temp:=a[st[h]];
           if a[i]>temp then
             begin
               t[i].less:=st[h];
               push(i);
               break;
             end;
           if a[i]=temp then  t[i].equal:=t[pop].equal
           else dec(h);
         end;
    end;
end;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   read(n);
   for i:=1 to n do
     read(a[i]);
   a[n+1]:=0;
   podschet;
   best:=0;
   for i:=1 to n do
     begin
       temp:=i;
       best:=max(best,a[i]*20);
       if (i=1) or (a[i]>a[i-1]) then
       while temp<>n+1 do
         begin
           k:=t[temp].less-i;
           k1:=20*a[temp];
           k:=k*k1;
           if k1*(n-i)<=best then break;
           best:=max(best,k);
           temp:=t[temp].less;
         end;
     end;
   write(best);
end.