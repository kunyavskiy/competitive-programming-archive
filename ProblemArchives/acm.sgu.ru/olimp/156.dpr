var n:integer;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(n);
case n of
2:begin
		writeln('0000');
		writeln('0110');
		writeln('0110');
		writeln('0000');
	end;
3:begin
		writeln('000000');
		writeln('011110');
		writeln('012210') ;
		writeln('012210')  ;
		writeln('011110')   ;
		writeln('000000')    ;
	end;
4:begin
		writeln('00000000');
		writeln('01111110');
		writeln('01222210');
		writeln('01233210') ;
		writeln('01233210');
		writeln('01222210') ;
		writeln('01111110');
		writeln('00000000');
		end;
1:begin
		writeln('00');
		writeln('00');
	end;
5:begin
		writeln('0000000000');
		writeln('0111111110');
		writeln('0122222210');
		writeln('0123333210');
		writeln('0123443210');
		writeln('0123443210');
		writeln('0123333210');
		writeln('0122222210');
		writeln('0111111110');
		writeln('0000000000');
		end;
6:begin
		writeln('000000000000');
		writeln('011111111110');
		writeln('012222222210');
		writeln('012333333210');
		writeln('012344443210');
		writeln('012345543210');
		writeln('012345543210');
		writeln('012344443210');
		writeln('012333333210');
		writeln('012222222210');
		writeln('011111111110');
		writeln('000000000000');
		end;
7: begin
		writeln('00000000000000');
		writeln('01111111111110');
		writeln('01222222222210');
		writeln('01233333333210');
		writeln('01234444443210');
		writeln('01234555543210');
		writeln('01234566543210');
		writeln('01234566543210');
		writeln('01234555543210');
		writeln('01234444443210');
		writeln('01233333333210');
		writeln('01222222222210');
		writeln('01111111111110') ;
		writeln('00000000000000');
		end;
8: begin
		writeln('0000000000000000');
		writeln('0111111111111110');
		writeln('0122222222222210');
		writeln('0123333333333210');
		writeln('0123444444443210');
		writeln('0123455555543210');
		writeln('0123456666543210');
		writeln('0123456776543210');
		writeln('0123456776543210');
		writeln('0123456666543210');
		writeln('0123455555543210');
		writeln('0123444444443210');
		writeln('0123333333333210');
		writeln('0122222222222210');
		writeln('0111111111111110');
		writeln('0000000000000000');
		end;
9: begin
		writeln('000000000000000000');
		writeln('011111111111111110');
		writeln('012222222222222210');
		writeln('012333333333333210');
		writeln('012344444444443210');
		writeln('012345555555543210');
		writeln('012345666666543210');
		writeln('012345677776543210');
		writeln('012345678876543210');
		writeln('012345678876543210');
		writeln('012345677776543210');
		writeln('012345666666543210') ;
		writeln('012345555555543210');
		writeln('012344444444443210') ;
		writeln('012333333333333210');
		writeln('012222222222222210');
		writeln('011111111111111110');
		writeln('000000000000000000');
		end;
10: begin
		writeln('00000000000000000000');
		writeln('01111111111111111110');
		writeln('01222222222222222210');
		writeln('01233333333333333210');
		writeln('01234444444444443210');
		writeln('01234555555555543210');
		writeln('01234566666666543210') ;
		writeln('01234567777776543210');
		writeln('01234567888876543210');
		writeln('01234567899876543210');
		writeln('01234567899876543210');
		writeln('01234567888876543210');
		writeln('01234567777776543210');
		writeln('01234566666666543210');
		writeln('01234555555555543210');
		writeln('01234444444444443210');
		writeln('01233333333333333210');
		writeln('01222222222222222210');
		writeln('01111111111111111110');
		writeln('00000000000000000000');
		end;
end;
end.


