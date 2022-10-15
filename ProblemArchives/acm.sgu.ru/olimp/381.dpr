{$apptype console}
var b:array [1..3] of integer;
		i:integer;
    procedure swap(var a,b:integer);
    var t:integer;
    begin
    t:=a;
    a:=b;
    b:=t;
    end;
begin
reset(input,'input.txt');
rewrite(output,'output.txt');
for i:=1 to 3 do
read(b[i]);
if b[1]>b[2] then swap(b[1],b[2]);
if b[1]>b[3] then swap(b[1],b[3]);
if b[2]>b[3] then swap(b[2],b[3]);
if b[2]-b[1]=b[3]-b[2] then write(b[3],' ',b[2],' ',b[1])
else write('-1')
end.