var  a:integer;


begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a);
  write(trunc(a*a/2)+2)
end.