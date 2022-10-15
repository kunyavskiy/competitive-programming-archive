var s:string[251];
    i,k:integer;
    PRED:BOOLEAN;
begin
  assign(input,'input.txt');
  reset(input);
  assign(output,'output.txt');
  rewrite(output);
  readln(s);
  k:=0;
  for i:=1 to length(s)do
    case s[i] of
  'A','E','I','O','U':  begin
                        k:=k+1;
                        pred:=true;
                        end;
  'Y':  if not((i=1) or pred =true) then
          begin
          k:=k+1;
          pred:=true;
          end
          else pred:=false
  else pred:=false
  end;
write(k,' ',length(s)-k);
end.