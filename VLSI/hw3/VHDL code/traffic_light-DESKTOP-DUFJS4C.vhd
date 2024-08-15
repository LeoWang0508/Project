library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity traffic_light is
 port(sensor: in std_logic;
	clk: in std_logic;
	r_light: out std_logic;
	g_light: out std_logic;
	y_light: out std_logic);
end traffic_light;

architecture behavior of traffic_light is
 type mstate is (green, yellow1, red, yellow2);
 signal state, next_state : mstate;
 signal enable : std_logic;
 signal reset : std_logic;
 signal complete : std_logic;
 signal count1, count2 : std_logic_vector(4 downto 0) := "00000";
 constant maximum : std_logic_vector(4 downto 0) := "00010";
 
begin
 process(sensor, state, reset, enable)
 begin      
   if enable = '1' and complete = '0' then
     count1 <= count2 + 1;
   end if;
   case state is 
    When green =>
      reset <= '1';
	  r_light <= '0';
	  g_light <= '1';
	  y_light <= '0';
	  if(sensor = '1') then
	    next_state <= yellow1;
	    reset <= '0';
	  else
		next_state <= green;
	  end if;
	   
	When red =>
	  enable <= '1';
	  r_light <= '1';
	  g_light <= '0';
	  y_light <= '0';
	  if complete = '1' then
	    next_state <= yellow2;
	    count1 <= "00000";
	  else
	  	next_state <= red;
	  end if;
	 
	When yellow1 =>
	  reset <= '0';
	  r_light <= '0';
	  g_light <= '0';
	  y_light <= '1';	
	  next_state <= red; 
	  count1 <= "00001";
	    
	When yellow2 =>
	  r_light <= '0';
	  g_light <= '0';
	  y_light <= '1';
	  next_state <= green;  
	  count1 <= (others => '0');
      enable <= '0'; 
   end case;  
 end process;
 
 process(complete)
 begin
    if count2 >= maximum then 
     complete <= '1';
   else
     complete <= '0';
   end if;
 end process;
 
 process
 begin   
   count2 <= count1;
   wait until clk'event and clk = '1';
   state <= next_state;  
 end process;
 
end behavior;