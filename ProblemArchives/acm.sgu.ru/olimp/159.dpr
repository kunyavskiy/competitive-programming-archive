{$APPTYPE CONSOLE}

uses
  SysUtils;

var a:array[0..150000] of integer;
    n,s,i,m:integer;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=0 to n-1 do
    read(a[i]);
  m:=0;
  i:=0;
  s:=0;
  while i<m+n do
     begin
      s:=s+a[i mod n];
      inc(i);
      if s<=0 then
       begin
        if i>=n then
          begin
            write('NO');
            close(input);
            close(output);
            halt;
          end;
        m:=i;
        s:=0;
        continue;
       end;
      if i=m+n then
         begin
          writeln('YES');
          write(m+1);
          break;
         end;
    end;
end.