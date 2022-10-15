{$APPTYPE CONSOLE}
{$O-,r+,q+}

uses
  SysUtils;


type lexem=(_del,_num,_plus,_minus,_mul,_open,_close,_end,_exp,_sin,_cos,_abs,_ln);
     curlexem=record
              lex:lexem;
              vl:extended;
              pos:integer;
              end;
var  curent:curlexem;
     per:array['a'..'z'] of extended;
     s:string;
     i,n:integer;
     a:extended;
     c,c1:char;

procedure usererror;
begin
  write('Error');
  close(input);
  close(output);
  halt;
end;

procedure userglobalerror;
begin
  halt(1);
end;

procedure nextlexem;
var k:extended;
begin
  case s[curent.pos] of
  '$':curent.lex:=_end;
  '(':curent.lex:=_open;
  ')':curent.lex:=_close;
  '+':curent.lex:=_plus;
  '-':curent.lex:=_minus;
  '/':curent.lex:=_del;
  '*':curent.lex:=_mul;
  '0'..'9':begin
             curent.lex:=_num;
             curent.vl:=ord(s[curent.pos])-ord('0');
             while s[curent.pos+1] in ['0'..'9'] do
               begin
                 inc(curent.pos);
                 curent.vl:=curent.vl*10+ord(s[curent.pos])-ord('0');
               end;
             if s[curent.pos+1]='.' then
               begin
                 inc(curent.pos,1);
                 k:=0.1;
                 while s[curent.pos+1] in ['0'..'9'] do
                 begin
                   inc(curent.pos);
                   curent.vl:=curent.vl+(ord(s[curent.pos])-ord('0'))*k;
                   k:=k/10;
                end;
               end;
           end;
  'E':begin
        curent.lex:=_exp;
        inc(curent.pos,2)
      end;
  'S':begin
        curent.lex:=_sin;
        inc(curent.pos,2)
      end;
  'C':begin
        curent.lex:=_cos;
        inc(curent.pos,2)
      end;
  'A':begin
        curent.lex:=_abs;
        inc(curent.pos,2)
      end;
  'L':begin
        curent.lex:=_ln;
        inc(curent.pos)
      end;
  'a'..'z':begin
             curent.lex:=_num;
             curent.vl:=per[s[curent.pos]];
           end;
  else userglobalerror;
  end;
  inc(curent.pos);
end;

function expr:extended;forward;

function mult:extended;
begin
  case curent.lex of
  _num:begin
        result:=curent.vl;
        nextlexem;
       end;
  _open:begin
         nextlexem;
         result:=expr;
         if curent.lex<>_close then userglobalerror;
         nextlexem;
        end;
  _minus:begin
           nextlexem;
           result:=-mult;
         end;
  _exp:begin
          nextlexem;
          result:=mult;
          result:=exp(result);
       end;
  _abs:begin
          nextlexem;
          result:=mult;
          result:=abs(result);
       end;
  _sin:begin
          nextlexem;
          result:=mult;
          result:=sin(result);
       end;
  _cos:begin
          nextlexem;
          result:=mult;
          result:=cos(result);
       end;
  _ln:begin
          nextlexem;
          result:=mult;
          if result<=0 then usererror;
          result:=ln(result);
       end;
  else userglobalerror;
end;
end;
function item:extended;
var a,b:extended;
begin
  a:=mult;
  while (curent.lex=_mul) or (curent.lex=_del) do
    begin
        if curent.lex=_mul then
         begin
         nextlexem;
         a:=a*mult
         end
        else
         begin
         nextlexem;
          b:=mult;
          if b=0 then usererror
          else a:=a/b;
         end;
     end;
  item:=a;
end;

function expr:extended;
var a:extended;
begin
  a:=item;
  while (curent.lex=_plus) or (curent.lex=_minus) do
    begin
      if curent.lex=_plus then
        begin
          nextlexem;
          a:=a+item;
         end
      else begin
            nextlexem;
            a:=a-item;
           end;
    end;
  expr:=a;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do
    begin
      read(c);
      read(c1);
      readln(a);
      per[c]:=a;
    end;
  readln(s);
  s:=s+'$';
  i:=1;
  while i<=length(s) do
    if s[i]=' ' then delete(s,i,1)
    else inc(i);
  curent.pos:=1;
  nextlexem;
  a:=expr;
  if curent.lex<>_end then userglobalerror;
  write(a:0:2);
end.