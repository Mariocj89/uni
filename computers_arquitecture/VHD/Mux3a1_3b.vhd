----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:45:48 10/13/2010 
-- Design Name: 
-- Module Name:    mux3a1_5b - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux3a1_5b is
    Port ( D0 : in  STD_LOGIC_VECTOR (4 downto 0);
           D1 : in  STD_LOGIC_VECTOR (4 downto 0);
           D2 : in  STD_LOGIC_VECTOR (4 downto 0);
           Sel : in  STD_LOGIC_VECTOR (1 downto 0);
           F : out  STD_LOGIC_VECTOR (4 downto 0));
end mux3a1_5b;

architecture Behavioral of mux3a1_5b is

begin

process (Sel, D0, D1, D2)
begin
	case CONV_INTEGER(Sel) is
		when 0 => F <= D0;
		when 1 => F <= D1;
		when 2 => F <= D2;
		when others => F <= (others => '0');
	end case;
end process;


end Behavioral;

