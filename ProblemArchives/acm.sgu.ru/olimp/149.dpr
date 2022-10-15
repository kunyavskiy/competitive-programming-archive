{$APPTYPE CONSOLE}



uses
  SysUtils;

const                         {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44}
    b:array[1..44] of integer=(1,2,3,3,4,4,4,5,5,5 ,5 ,6 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,9, 9, 9 ,9 ,9 ,9 ,9 ,10 ,10  ,10 );

var  a:array[0..44] of int64;
     j,i,r:integer;
     c:char;

procedure QSort(left, right : integer);
var m, i, j, t : integer;
begin
  m := a[(left+right) div 2];
  i := left; j := right;
  repeat
    while a[i] > m do inc(i); {&#239;&#229;&#240;&#226;&#251;&#233; while}
    while a[j] < m do dec(j); {&#226;&#242;&#238;&#240;&#238;&#233; while}
    if i <= j then
    begin
      t := a[i]; a[i] := a[j]; a[j] := t;
      inc(i); dec(j);
    end;
  until i > j;

  if j > left then QSort(left, j);
  if i < right then QSort(i, right);
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not seekeof do
    begin
      read(c);
      if c in ['A'..'Z'] then
        inc(a[ord(c)-ord('A')+1])
      else
        if c in ['a'..'z'] then
          inc(a[ord(c)-ord('a')+1])
      else
        case c of
        '0'..'9':inc(a[27+ord(c)-ord('0')]);
        '.':inc(a[37]);
        ',':inc(a[38]);
        '!':inc(a[39]);
        '?':inc(a[40]);
        ';':inc(a[41]);
        ':':inc(a[42]);
        '-':inc(a[43]);
        '_':inc(a[44]);
        else halt(1);
        end;
    end;
  qsort(1,44);
  r:=0;
  for i:=1 to 44 do
      r:=r+a[i]*b[i];
  write(r);
end.