library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity D_FF_en is 
  port(Qin, Qin2 : in integer range 0 to 7;
       clk, en : in std_logic;
       Qout : out integer range 0 to 7);
  end D_FF_en;
architecture behavior of D_FF_en is
 begin 
 process (Qin,en)
   begin 
     if (clk'EVENT and clk='1' and en='0') then
        Qout <= Qin;          --before
     elsif (clk'EVENT and clk='1') then
        Qout <= Qin2;             --now
     end if;
   end process;
  end behavior;