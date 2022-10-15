var a:INTEGER;
b:char;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(b);
read(a);
case a of
1,8: case b of
		 'A','H':write('2');
		 'B','G':write ('3');
		 'C','D','E','F':write('4');
		 end;
2,7: case b of
		 'A','H':write('3');
		 'B','G':write ('4');
		 'C','D','E','F':write('6');
		end;
else  case b of
		 'A','H':write('4');
		 'B','G':write ('6');
		 'C','D','E','F':write('8');
		 end;
end;
end.