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



procedure D is

g,g2 : array(1..100) of unbounded_string;
n : Integer; 
begin
   N := Integer'Value(Get_Line);
   for i in 1 .. n loop
      g(i) := To_Unbounded_String(Get_Line);
      g2(i) := g(i);
   end loop;
   for k in 1 .. n loop
	   for i in 1 .. n loop
		   for j in 1 .. n loop
		       if (To_String(g(i))(k) = 49 and To_String(g(k))(j) = 49) then
		           g(i)(j) := 49;
		       end if;
		   end loop;
	   end loop;
   end loop;
end D;

