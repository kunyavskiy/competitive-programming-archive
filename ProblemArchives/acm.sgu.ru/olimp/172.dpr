 var N,K:integer;
 begin
 assign(input,'input.txt');
 assign(output,'output.txt');
 reset(input);
 rewrite(output);
 read(N);
 read(K);
 if N mod K=0 then write(N div K)
 else write(N div K +1)
 end.