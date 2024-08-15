library ieee;
use std.textio.all;
use ieee.std_logic_1164.all;
use ieee.std_logic_textio.all;

entity test_bench_3 is
end;
--
architecture arch_test of test_bench_3 is
--
signal clk: std_logic := '0';
signal sel: std_logic;
signal seed : std_logic_vector(63 downto 0);
signal rng_out : std_logic_vector(63 downto 0);
--
component RNG 
  port(seed : in std_logic_vector(63 downto 0);
       clk : in std_logic;
       sel : in std_logic;
       rng_out : out std_logic_vector(63 downto 0)
   );
end component;
--
begin
-- Set a clock with period 100 ns
  clk <= '1' after 50 ns when clk='0' else
         '0' after 50 ns; 
-- Set sel
  sel <= '0', '1' after 100 ns;
--
-- This is the process for reading data from a text file
--
process
  file source_data : text is in "source_data.txt";
  variable in_data : line;
  variable temp : std_logic_vector(63 downto 0); 
--
  begin
     readline(source_data,in_data);
     read(in_data,temp);  
     seed <= temp;
    wait;
end process;
--
-- This is the entity under test
--
TEST_TARGET: RNG port map (seed,clk,sel,rng_out);
--
-- This is the process for writing simulation results to a text file
--
process(rng_out)
file output_data : text is out "output_data.txt";
variable out_data : line;
begin
-- if(rng_out /= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU")then
 if (rng_out /= (rng_out'range => 'U')) then
 write(out_data,rng_out);
 writeline(output_data,out_data);
 end if;
end process;
end arch_test;
