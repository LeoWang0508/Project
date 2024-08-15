library ieee;
use ieee.std_logic_1164.all;

entity D_FF is 
  port  (Qin, clk : in bit;
         Qout : out bit);
  end D_FF;
architecture behavior of D_FF is
 begin 
 process (Qin,clk)
   begin 
     if (clk'EVENT and clk='1') then
        Qout <= Qin;
     end if;
   end process;
  end behavior;