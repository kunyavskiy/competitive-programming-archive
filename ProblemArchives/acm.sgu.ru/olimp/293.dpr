{$APPTYPE CONSOLE}

uses
  sysutils,math;

var n,i,k:integer;
    c:char;
    a,st:array[1..1000] of integer;
begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 readln(n);
 for i:=n downto 1 do
  begin
   readln(c);
   if c='D' then 
   	a[i]:=0
   else
    a[i]:=1;
  end;
 k:=0;
 for i:=1 to n do
 	if (a[i]+k) mod 2=0 then
	 begin
  	inc(k);
	  st[k]:=i;
 end;
 writeln(k);
 for i:=k downto 1 do 
 	write(n-st[i]+1,' ');
end.