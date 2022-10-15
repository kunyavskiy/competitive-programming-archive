{$APPTYPE CONSOLE}

uses
  SysUtils;

var s:string[2];

begin
 reset(input,'input.txt');
 rewrite(output,'output.txt');
 read(s);
 case s[1] of
  'A': case s[2] of
       '1':write('A1B3A5C4A3B1D2E4C5A4B2D1C3B5D4E2C1A2B4D5E3C2E1D3E5');
       '2':write(0);
       '3':write('A3B1C3B5D4E2C1A2B4D5E3D1B2A4C5E4D2B3A1C2E1D3E5C4A5');
       '4':write(0);
       '5':write('A5B3A1C2A3B5D4E2C1A2B4D5C3B1D2E4C5A4B2D1E3C4E5D3E1');
       end;
  'B':  case s[2] of
       '1':write(0);
       '2':write('B2A4C3D1E3D5B4A2C1E2D4B5A3B1D2E4C5B3A1C2E1D3E5C4A5');
       '3':write(0);
       '4':write('B4A2C3D5E3D1B2A4C5E4D2B1A3B5D4E2C1B3A5C4E5D3E1C2A1');
       '5':write(0);
       end;
  'C':  case s[2] of
       '1':write('C1A2B4D5C3E2D4B5A3B1D2E4C5A4B2D1E3C2A1B3A5C4E5D3E1');
       '2':write(0);
       '3':write('C3A2B4D5E3D1B2A4C5E4D2B1A3B5D4E2C1B3A1C2E1D3E5C4A5');
       '4':write(0);
       '5':write('C5A4B2D1C3E4D2B1A3B5D4E2C1A2B4D5E3C4A5B3A1C2E1D3E5');
       end;
  'D':  case s[2] of
       '1':write(-1);
       '2':write('D2E4C3B1A3B5D4E2C1A2B4D5E3D1B2A4C5D3E1C2A1B3A5C4E5');
       '3':write(0);
       '4':write('D4E2C3B5A3B1D2E4C5A4B2D1E3D5B4A2C1D3E5C4A5B3A1C2E1');
       '5':write(0);
       end;
  'E':  case s[2] of
       '1':write('E1D3E5C4E3D1B2A4C5E4D2B1C3D5B4A2C1E2D4B5A3C2A1B3A5');
       '2':write(0);
       '3':write('E3D1C3D5B4A2C1E2D4B5A3B1D2E4C5A4B2D3E1C2A1B3A5C4E5');
       '4':write(0);
       '5':write('E5D3E1C2E3D5B4A2C1E2D4B5C3D1B2A4C5E4D2B1A3C4A5B3A1');
       end;
  end;
end.