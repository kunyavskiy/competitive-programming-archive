 var N,P:integer;
 begin
 assign(input,'input.txt');
 assign(output,'output.txt');
 reset(input);
 rewrite(output);
 read(N);
 read(P);
 write(P*N);
 end.