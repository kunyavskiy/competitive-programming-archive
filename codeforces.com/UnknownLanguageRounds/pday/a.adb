with Ada.Text_IO,
     Ada.Characters.Handling,
     Ada.Float_Text_IO; 
 use Ada.Text_IO,
     Ada.Characters.Handling,
     Ada.Float_Text_IO;

procedure A is
   Text: String(1..100);
   Length: Natural;
   Was_Space: Boolean := True;
   I: Integer := 1;
   p, total: Float;
begin
   Get_Line(Text, Length);
   Text := To_Lower(Text);
   Get(Item => p);
   total := 0.0;
   loop
      if Character'Pos(Text(I)) = 63 then
          total := total + p;
      else if Character'Pos(Text(I)) = 49 then
          total := total + 1.0;
          end if;
      end if;
      I := I + 1; 
      exit when I > Length;
   end loop;
   total := total / Float(Length);
   Put(total, Exp => 0);
end a;
