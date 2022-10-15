{$APPTYPE CONSOLE}

uses
  SysUtils;

var shar,mat,pech:array[0..200] of integer;
    t,i,n,m,k,tok:integer;
    sh,ma,pe:boolean;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(t,n,k,m);
  shar[0]:=1;
  mat[0]:=1;
  pech[0]:=1;
  for i:=1 to 2*n do
    read(shar[i]);
  for i:=1 to 2*k do
    read(mat[i]);
  for i:=1 to 2*m do
    read(pech[i]);
  sh:=true;
  ma:=true;
  pe:=false;
  tok:=0;
  for i:=1 to pech[2*m] do
   begin
     if (mat[0]<=2*n) and (mat[mat[0]]=i)   then begin ma:=not ma; inc(mat[0]) end;
     if (shar[0]<=2*k) and (shar[shar[0]]=i)  then begin sh:=not sh; inc(shar[0]) end;
     if (pech[0]<=2*m) and (pech[pech[0]]=i) and not pe then begin pe:=not pe; inc(pech[0]) end;
     if ma and sh and pe then inc(tok)
       else tok:=0;
     if tok=t then
     begin
       write(i-t+1);
       close(input);
       close(output);
       halt;
     end;
     if (pech[0]<=2*m) and (pech[pech[0]]=i) and pe then begin pe:=not pe; inc(pech[0]) end;
   end;
  write('NO')
end.