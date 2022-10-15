var 
a, b : longint; 
begin 
  assign(input, 'input.txt'); 
  reset(input); 
  assign(output, 'output.txt'); 
  rewrite(output); 
  read(a, b); 
  writeln(2*b - a); 
  close(input); 
  close(output); 
end.