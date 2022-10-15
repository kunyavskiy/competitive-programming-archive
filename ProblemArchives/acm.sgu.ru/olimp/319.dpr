{$APPTYPE CONSOLE}
{$o+}
uses
  SysUtils;
const base=1 shl 12-1;
type int=longint;
      cou =record
      name:string;
      g:int;
      s:int;
      b:int;
      p:int;
      next:int;
      end;
var  a:array[1..10000] of cou;
     b:array[1..base] of integer;
     s1:string;
     ka,i,h,c,n,j,pc:int;
     se:char;
function ravn (a1,a2:cou):boolean;
begin
ravn:=(a1.g=a2.g) and (a1.s=a2.s) and (a1.b=a2.b);
end;
function bol (a1,a2:cou):boolean;
begin
if a1.g>a2.g then bol:=true
 else if a1.g=a2.g then
          if a1.s>a2.s then bol:=true
          else if a1.s=a2.s then
                  if a1.b>a2.b then bol:=true
                  else if a1.b=a2.b then bol:=a1.name<a2.name
                       else  bol:=false
                  else  bol:=false
      else bol:=false
end;
procedure QSort(left, right :  integer);
var i, j: integer;
    m,t:cou;
begin
  m := a[random(right-left)+left];
  i := left; j := right;
  repeat
    while bol(a[i],m) do inc(i); {первый while}
    while bol(m,a[j]) do dec(j); {второй while}
    if i <= j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;

function hash (var s:string):int;
var i:int;
    r:int;
begin
r:=0;
for i:=1 to length(s) do
r:=(r*239+ord(s[i])) and base;
hash:=r;
end;
procedure add (var l:int;x:int;var st:string);
begin
inc(ka);
a[ka].name:=st;
a[ka].next:=l;
case x of
1:a[ka].g:=1;
2:a[ka].s:=1;
3:a[ka].b:=1;
end;
l:= ka;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
ka:=0;
readln(n);
for i:=1 to n do
begin
for j:=1 to 3 do
begin
read(se);
s1:=se;
read(se);
s1:=s1+se;
read(se);
s1:=s1+se;
if j=3 then readln
else read(se);
h:=hash(s1);
if b[h]=0 then
begin
inc(ka);
b[h]:=ka;
a[ka].name:=s1;
case j of
1:a[ka].g:=1;
2:a[ka].s:=1;
3:a[ka].b:=1;
end;
end
else
begin
c:=b[h];
while not((a[c].next=0) or (a[c].name=s1)) do c:=a[c].next;
if not(a[c].name=s1)  then add(b[h],j,s1)
else
case j of
1:inc(a[c].g);
2:inc(a[c].s);
3:inc(a[c].b);
end;
end;
end;
end;
qsort(1,ka);
a[1].p:=1;
pc:=1;
for i:=2 to ka do
begin
inc(pc);
if ravn(a[i],a[i-1]) then a[i].p:=a[i-1].p
else a[i].p:=pc;
end;
for i:=1 to ka do writeln(a[i].p,'. ',a[i].name,' ',a[i].g,' ',a[i].s,' ',a[i].b);
end.