{$APPTYPE CONSOLE}
{$I-;O+;R-;Q-;H+}
uses
  SysUtils;
var s,s1:string;
    i:integer;
procedure analis(var c:STRING);
var b:integer;
begin
if not (s1='') then
begin
b:=strtoint(s1);
s1:='';
case b of
1:write('A');
2..3:write('B');
4..6:write('C');
7..10:write('D');
11..15:write('E');
16..21:write('F');
22..28:write('G');
29..36:write('H');
37..45:write('I');
46..55:write('J');
56..66:write('K');
67..78:write('L');
79..91:write('M');
92..105:write('N');
106..120:write('O');
121..136:write('P');
137..153:write('Q');
154..171:write('R');
172..190:write('S');
191..210:write('T');
211..231:write('U');
232..253:write('V');
254..276:write('W');
277..300:write('X') ;
301..325:write('Y');
326..351:write('Z');
end;
end;
end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
readln(s);
for i:=1 to length(s) do
case s[i] of
'1','2','3','4','5','6','7','8','9','0':s1:=s1+s[i];
' ':analis(s1);
'/':
begin
analis(s1);
write(' ');
end;
end;
analis(s1);
end.