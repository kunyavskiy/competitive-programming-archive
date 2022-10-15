{$APPTYPE CONSOLE}
{$R+,Q+}


var a,b,c:integer;

procedure swap(var a,b:integer);
var t:integer;
begin
  t:=a;
  a:=b;
  b:=t;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,c);
  if a>c then swap(a,c);
  if b>c then swap(b,c);
  if (a=b) and (a=0) then
    begin
      writeln('Yes');
      write(a,' ',c,' ',b);
      close(input);
      close(output);
      halt;
    end;
  if a*b<>c then write('No')
    else
    begin
      writeln('Yes');
      writeln(a,' ',b,' ',c)
    end;
  close(input);
  close(output);
end.