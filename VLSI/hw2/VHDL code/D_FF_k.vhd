library ieee;
use ieee.std_logic_1164.all;

entity D_FF_k is 
  generic(k : integer := 7);
  port(Qin : in std_logic_vector(k downto 0);
       clk : in bit;
       Qout : out std_logic_vector(k downto 0));
  end D_FF_k;
architecture behavior of D_FF_k is
 begin 
 process (Qin,clk)
   begin 
     if (clk'EVENT and clk='1') then
        Qout <= Qin;
     end if;
   end process;
  end behavior;