{$APPTYPE CONSOLE}

var n,goris,vert:integer;

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 read(n);
 goris:=(n div 2);
 vert:=n-goris;
 write((vert+1)*(goris+1))
end.