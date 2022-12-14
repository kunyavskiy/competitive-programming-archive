with Ada.Text_IO,
     Ada.Characters.Handling,
     Ada.Float_Text_IO,
     Ada.Integer_Text_IO,
     Ada.Strings.Unbounded; 
 use Ada.Text_IO,
     Ada.Characters.Handling,
     Ada.Float_Text_IO,
     Ada.Integer_Text_IO,
     Ada.Strings.Unbounded;



procedure C is

y,d,m,ans : Integer;
inp : unbounded_string;
n : Integer;

function Weekday (DDay, MMonth, YYear : Integer) return Integer is
        Day, Month, Year, Century : Integer;
    begin
        Day := DDay;
        Month := MMonth;
        Year := YYear;
        if Month < 3 then
            Year  := Year - 1;
            Month := Month + 10;
        else
            Month := Month - 2;
        end if;
        Century := Year / 100;        -- first two digits of Year
        Year    := Year mod 100;      -- last two digits of Year
        return (((26*Month - 2)/10 + Day + Year + Year/4 + Century/4 - 2*Century) mod 7);
    end Weekday;

begin
   inp := To_Unbounded_String(Get_Line);
   n := Integer'Value(To_String(inp));
   ans := 0;
   for i in 1 .. n loop
      inp := To_Unbounded_String(Get_Line);
      y := Integer'Value(To_String(inp)(1..4));
      m := Integer'Value(To_String(inp)(6..7));
      d := Integer'Value(To_String(inp)(9..10));
      if Weekday(d,m,y) = 5 and d = 13 then ans := ans + 1; end if;
      New_Line;
   end loop;  
   Put(ans, Width=>0); 
end C;

