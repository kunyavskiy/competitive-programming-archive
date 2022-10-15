var a1,a2,b1,b2,i,k:integer;
		za:array[1..1000] of boolean;
function min(a,b:integer):integer;
begin
if a<=b then min:=a
else min:=b;
end;
function max(a,b:integer):integer;
begin
if a>=b then max:=a
else max:=b;
end;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
read(a1,a2,b1,b2);
for i:=min(a1,a2) to max(a1,a2) do  za[i]:=true;
for i:=min(b1,b2) to max(b1,b2) do za[i]:=true;
k:=0;
for i:=1 to 1000 do if za[i]=true then inc(k);
write(k);
end.
