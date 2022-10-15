{$apptype console}

const por:array[1..24,1..4] of integer=
        ((1,2,3,4),(1,2,4,3),(1,3,2,4),(1,3,4,2),(1,4,2,3),(1,4,3,2),
         (2,1,3,4),(2,1,4,3),(2,3,1,4),(2,3,4,1),(2,4,1,3),(2,4,3,1),
         (3,1,2,4),(3,1,4,2),(3,2,1,4),(3,2,4,1),(3,4,1,2),(3,4,2,1),
         (4,1,2,3),(4,1,3,2),(4,2,1,3),(4,2,3,1),(4,3,1,2),(4,3,2,1));

var st,st1:string;
    used:array[1..20,1..20,1..20,1..20] of boolean;

function generate(s,s1:string;t,lf,rg,lf1,rg1:integer):string;
var l,l1,i:integer;
begin
  if used[lf,rg,lf1,rg1] then
    begin
      result:='-1';
      exit;
    end;
  if not ((s=copy(st,lf,rg-lf+1)) and (s1=copy(st1,lf1,rg1-lf1+1))) then halt(1);
  used[lf,rg,lf1,rg1]:=true;
  if length(s)=0 then
    begin
      l:=length(s1);
      for i:=1 to length(s1) div 2 do
        if s1[i]<>s1[l-i+1] then
         begin
          result:='-1';
          exit;
         end;
      result:=s1;
      exit;
    end;
  if length(s1)=0 then
    begin
      l:=length(s);
      for i:=1 to length(s) div 2 do
        if s[i]<>s[l-i+1] then
         begin
          result:='-1';
          exit;
         end;
      result:=s;
      exit;
    end;
  result:='-1';
  l:=length(s);
  l1:=length(s1);
  for i:=1 to 4 do
  case por[t,i] of
  1:if (l>1) and (s[1]=s[l]) then
      begin
        result:=generate(copy(s,2,l-2),s1,random(24)+1,lf+1,rg-1,lf1,rg1);
        if result<>'-1' then
         begin
          result:=s[1]+result+s[1];
          exit;
         end;
      end;
  2:if (l1>1) and (s1[1]=s1[l1]) then
      begin
        result:=generate(s,copy(s1,2,l1-2),random(24)+1,lf,rg,lf1+1,rg1-1);
        if result<>'-1' then
         begin
          result:=s1[1]+result+s1[1];
          exit;
         end;
      end;
  3:if (s[1]=s1[l1]) then
      begin
        result:=generate(copy(s,2,l-1),copy(s1,1,l1-1),random(24)+1,lf+1,rg,lf1,rg1-1);
        if result<>'-1' then
         begin
          result:=s[1]+result+s[1];
          exit;
         end;
      end;
   4:if (s[l]=s1[1]) then
      begin
        result:=generate(copy(s,1,l-1),copy(s1,2,l1-1),random(24)+1,lf,rg-1,lf1+1,rg1);
        if result<>'-1' then
         begin
          result:=s1[1]+result+s1[1];
          exit;
         end;
      end;
   end;

end;



begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  randomize;
  readln(st);
  readln(st1);
  write(generate(st,st1,random(24)+1,1,length(st),1,length(st1)));
end.