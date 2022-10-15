{$apptype console}
{$R+,Q-,O-}

program black_and_white;

uses
  SysUtils;

const
    maxn = 50000;

function bsq(x, y: int64): int64;
begin
    if (x * y) mod 2 = 0 then
        bsq := x * y div 2
    else
        bsq := (x * y + 1) div 2;
end;

var
    i, n: longint;
    x, y: array [1..maxn + 1] of int64;
    b, w, db, dw: int64;
    s1, s2, s: int64;

begin
    reset(input, 'input.txt');
    rewrite(output, 'output.txt');

    read(n);
    for i := 1 to n do begin
        read(x[i], y[i]);
        assert(abs(x[i]) <= 1000000000);
        assert(abs(y[i]) <= 1000000000);
    end;
    x[n + 1] := x[1];
    y[n + 1] := y[1];

    s := 0;
    for i := 1 to n do begin
        assert((x[i] = x[i + 1]) xor (y[i] = y[i + 1]));
        s := s + (x[i] - x[i + 1]) * (y[i] + y[i + 1]);
    end;

    assert(s >= 0);
        

    b := 0;
    w := 0;

    for i := 1 to n do begin
        if x[i] <> x[i + 1] then begin
            db := bsq(x[i], y[i]) - bsq(x[i + 1], y[i + 1]);
            dw := (x[i] - x[i + 1]) * y[i] - db;
            b := b + db;
            w := w + dw;
        end;
    end;

    writeln(b, ' ', w);

    close(input);
    close(output);
end.