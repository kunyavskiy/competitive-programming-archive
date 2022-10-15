 var N:integer;
 begin
 assign(input,'input.txt');
 assign(output,'output.txt');
 reset(input);
 rewrite(output);
 read(N);
 if N>0 then
 write(N div 2 )
 else write('0')
 end.