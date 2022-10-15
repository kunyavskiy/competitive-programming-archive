{$APPTYPE CONSOLE}
{$O+}

uses
  Math;



var i,n,kol,x,j:integer;
    from:array[0..22,0..1000000] of shortint;
    c:array[1..22] of integer;
procedure print(a,b:integer);
begin
  if a=0 then
     begin
       writeln(kol);
       exit;
     end;
  if from[a,b]=0 then print(a-1,b);
  if from[a,b]=1 then
    begin
      inc(kol);
      print(a-1,b-c[a]);
      write(c[a],' ');
    end;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,x);
  for i:=1 to n do
     read(c[i]);
  fillchar(from,sizeof(from),-1);
  from[0,0]:=0;
  for i:=1 to n do
    for j:=0 to x do
      begin
        if from[i-1,j]<>-1 then
            from[i,j]:=0
        else
        if (j>=c[i]) and (from[i-1,j-c[i]]<>-1) then
             from[i,j]:=1;
      end;
  if from[n,x]<>-1 then
     begin
       writeln('Yes');
       print(n,x);
     end
  else
    write('No');
end.