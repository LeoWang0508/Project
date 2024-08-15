library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
entity simple_ALU is
port(
   A,B : in unsigned(3 downto 0) ;
   S : in  std_logic_vector(1 downto 0);
   Y : out unsigned(7 downto 0)
   );
end simple_ALU ;

architecture dataflow of simple_ALU is 
begin
  with S select
  Y <= ("0000" & A) and ("0000" & B) when "00",
       A * B when "01",
       ("0000" & A) + ("0000" & B) when "10",
	   ("0000" & A) / ("0000" & B) when "11";
end dataflow;
