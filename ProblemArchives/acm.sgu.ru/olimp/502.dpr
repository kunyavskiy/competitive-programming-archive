{$APPTYPE CONSOLE}

uses
  SysUtils;

type naprav=(_start,_down,_up,_left,_right);
var t:array[0..51,0..51] of boolean;
    used:array[0..51,0..51] of boolean;
    n,m,i,j,res:integer;
    c:char;

function dfs(x,y:integer;nap:naprav):boolean;
var qu,qd,ql,qr:boolean;
begin
  case nap of
  _start:begin
         if used[x,y] then
          begin
           result:=false;
           exit;
          end;
          used[x,y]:=true;
          if  not t[x,y] then
            begin
              result:=false;
              exit;
            end;
          qu:=t[x-1,y];
          qd:=t[x+1,y];
          ql:=t[x,y-1];
          qr:=t[x,y+1];
          result:=(qu xor qd) and (ql xor qr);
          if not result then exit;
          if qu and ql then
            result:=dfs(x-1,y,_up) and dfs(x,y-1,_left);
          if qu and qr then
              result:=dfs(x-1,y,_up) and dfs(x,y+1,_right);
          if qd and ql then
              result:=dfs(x+1,y,_down) and dfs(x,y-1,_left);
          if qd and qr then
              result:=dfs(x+1,y,_down) and  dfs(x,y+1,_right);
         end;
  _up:result:=(not t[x,y]) or ((not t[x,y-1]) and (not t[x,y+1]) and dfs(x-1,y,_up));
  _down:result:=(not t[x,y]) or ((not t[x,y-1]) and (not t[x,y+1]) and dfs(x+1,y,_down));
  _left:result:=(not t[x,y]) or ((not t[x-1,y]) and (not t[x+1,y]) and dfs(x,y-1,_left));
  _right:result:=(not t[x,y]) or ((not t[x-1,y]) and (not t[x+1,y]) and dfs(x,y+1,_right));
  end;
  used[x,y]:=true;
end;

begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not seekeof do
    begin
      readln(n,m);
      fillchar(t,sizeof(t),false);
      fillchar(used,sizeof(used),false);
      for i:=1 to n do
       begin
        for j:=1 to m do
          begin
            read(c);
            t[i,j]:=c='*';
          end;
          readln;
        end;
        res:=0;
      for i:=1 to n do
        for j:=1 to m do
        if   dfs(i,j,_start) then
          inc(res);
      writeln(res);
    end;
end.