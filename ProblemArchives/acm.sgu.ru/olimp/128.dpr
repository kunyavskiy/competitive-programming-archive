{$APPTYPE CONSOLE}
{$R+,Q+}

var k,n,i,l,s,spos:integer;
    cost:array[1..11] of integer;
    q:boolean;
function  len(a,b,c,d,num:integer):boolean;
begin
   if num=n+1 then
     begin
       result:=a=0;
       result:=result and (b=0);
       result:=result and (c=0);
       result:=result and (d=0);
       exit;
     end;
   result:=false;
   if (not result) and (a>=cost[num]) then
      result:=len(a-cost[num],b,c,d,num+1);
   if (not result) and (b>=cost[num]) and (b<>a) then
      result:=len(a,b-cost[num],c,d,num+1);
   if (not result) and (c>=cost[num]) and (c<>a) and (c<>b) then
      result:=len(a,b,c-cost[num],d,num+1);
   if (not result) and (d>=cost[num]) and (d<>a) and (d<>b) and (d<>c) then
      result:=len(a,b,c,d-cost[num],num+1);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k,n);
  if n<=3 then
    begin
      for i:=1 to k do
        writeln('NO');
      close(input);
      close(output);
      halt;
    end;
  for l:=1 to k do
    begin
      for i:=1 to n do
        read(cost[i]);
      s:=0;
      for i:=1 to n do
        s:=s+cost[i];
      if s and 3<>0 then
        begin
          writeln('NO');
          continue;
        end;
      s:=s shr 2;
      q:=false;
      for i:=1 to n do
        if cost[i]>s then
          begin
            writeln('NO');
            q:=true;
            break;
          end;
      if q then continue;
      if len(s,s,s,s,1) then
        writeln('YES')
      else writeln('NO');
    end;
end.