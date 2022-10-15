{$APPTYPE CONSOLE}

uses
   Math;

var a:array[1..200,1..200] of integer;
    used:array[1..200,1..200] of boolean;
    answer:array[1..200,1..200] of integer;
    n,m,k,i,j,i1,j1,ma,kol:integer;
    c:char;

procedure dfs(i,j:integer);
begin
  used[i,j]:=true;
  if (i<n) and (a[i+1,j]<2) and (not used[i+1,j]) then dfs(i+1,j);
  if (i>1) and (a[i-1,j]<2) and (not used[i-1,j]) then dfs(i-1,j);
  if (j<m) and (a[i,j+1]<2) and (not used[i,j+1]) then dfs(i,j+1);
  if (j>1) and (a[i,j-1]<2) and (not used[i,j-1]) then dfs(i,j-1);
  if (i<n) and (a[i+1,j]=2) then inc(k);
  if (i>1) and (a[i-1,j]=2) then inc(k);
  if (j<m) and (a[i,j+1]=2) then inc(k);
  if (j>1) and (a[i,j-1]=2) then inc(k);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do
    begin
      for j:=1 to m do
        begin
          read(c);
          if c='.' then a[i,j]:=0;
          if c='*' then a[i,j]:=1;
          if c='+' then a[i,j]:=2;
        end;
      readln;
    end;
  fillchar(answer,sizeof(answer),-1);
  for i:=1 to n do
    for j:=1 to m do
     if (answer[i,j]=-1) and (a[i,j]=1) then
      begin
        k:=0;
        dfs(i,j);
       { for i:=1 to n do
          for j:=1 to m do
            if (used[i,j]) and (answer[i,j]=-1) then
              begin
                if (i<n) and (a[i+1,j]=2) then inc(k);
                if (i>1) and (a[i-1,j]=2) then inc(k);
                if (j<n) and (a[i,j+1]=2) then inc(k);
                if (j>1) and (a[i,j-1]=2) then inc(k);
              end;   }
       for i1:=1 to n do
         for j1:=1 to m do
           if (used[i1,j1]) and (answer[i1,j1]=-1) then
             answer[i1,j1]:=k;
      end;
  ma:=0;
  kol:=0;
  for i:=1 to n do
    for j:=1 to m do
     if a[i,j]=1 then
        if answer[i,j]>ma then
          begin
            ma:=answer[i,j];
            kol:=1;
          end
        else
        if answer[i,j]=ma then inc(kol);
  write(ma,' ',kol);
end.