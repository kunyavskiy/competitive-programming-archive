{$APPTYPE CONSOLE}

uses
  SysUtils;

var s:string;
    t,from:array[1..100,-1000..1000] of boolean;
    i,j:integer;

function ci(c:char):integer;
begin
  result:=ord(c)-ord('0');
end;

procedure print(x,v:integer);
begin
  if x=1 then
   begin
     write(s[1]);
     exit;
   end;
  if from[x,v] then
    begin
     print(x-1,v-ci(s[x]));
     write('+',s[x]);
     exit;
    end;
  print(x-1,v+ci(s[x]));
  write('-',s[x]);
end;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  fillchar(t,sizeof(t),false);
  t[1,ci(s[1])]:=true;
  for i:=2 to length(s) do
    for j:=-900 to 900 do
      begin
        if t[i-1,j-ci(s[i])] then
          begin
            t[i,j]:=true;
            from[i,j]:=true;
          end;
        if t[i-1,j+ci(s[i])] then
          begin
            t[i,j]:=true;
            from[i,j]:=false;
          end;
      end;
  if not t[length(s),0] then
    begin
      writeln('NO');
      close(input);
      close(output);
      halt;
    end;
  writeln('YES');
  print(length(s),0);

end.
