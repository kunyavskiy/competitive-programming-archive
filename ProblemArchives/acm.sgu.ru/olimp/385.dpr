{$APPTYPE CONSOLE}

var maxr,i,j,n,t,lastrasn:integer;
    s,maxs:string;
    rasn:array[0..2500,'A'..'Z'] of integer;
    q:boolean;



function rasnoobr(l,r:integer):integer;
var i:char;
    t:integer;
begin
  if l=r then
  begin
    result:=1;
    lastrasn:=1;
    exit;
  end;
  result:=lastrasn;
  t:=rasn[r-1,s[r]]-rasn[l-1,s[r]];
  if t=0 then inc(result);
  if t=1 then dec(result);
  lastrasn:=result;
end;

function min(a,b:string):string;
begin
 if a<b then result:=a
 else result:=b;
end;

begin
   reset(input,'input.txt');
   rewrite(output,'output.txt');
   readln(s);
   n:=length(s);
   for i:=1 to n do
     begin
       rasn[i]:=rasn[i-1];
       inc(rasn[i,s[i]]);
     end;
   maxr:=-1;
   maxs:='';
   for i:=1 to n do
   begin
     q:=false;
     for j:=i to n do
       begin
         t:=rasnoobr(i,j);
         if (maxr=t) and (not q) then
           begin
             maxs:=min(maxs,copy(s,i,j-i+1));
             q:=true;
           end;
         if maxr<t then
            begin
              maxr:=t;
              q:=true;
              maxs:=copy(s,i,j-i+1);
            end;
       end;
     if maxr>n-i then break;
     if maxr=26 then break;
   end;
   write(maxs);
end.