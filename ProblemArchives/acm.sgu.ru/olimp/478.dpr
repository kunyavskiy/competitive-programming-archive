{$APPTYPE CONSOLE}

uses
  SysUtils;

var test:array[1..100] of integer;
    neadtest:array[1..1000] of integer;
    bal,neadbal,n,m,i,k,j:integer;
    q:boolean;
    facultet,specialnost:string;

procedure getmark(pr:integer);
var a,b,i:integer;
begin
  a:=test[pr];
  bal:=bal+2;
  for i:=1 to 3 do
    begin
      read(b);
      if a>=b then inc(bal);
    end;
end;




begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to m do
    read(test[i]);
  readln;
  q:=false;
  for i:=1 to n do
   begin
      readln(facultet);
      bal:=0;
      read(k);
      for j:=1 to k do
        read(neadtest[j]);
      for j:=1 to k do
        getmark(neadtest[j]);
      readln(k);
      for j:=1 to k do
       begin
         readln(specialnost);
         readln(neadbal);
         if bal>=neadbal then
           begin
             writeln(facultet+' '+specialnost);
             q:=true;
           end;
       end;
   end;
 if not q then write('Army');
end.