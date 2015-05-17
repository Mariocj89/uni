----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:05:00 10/07/2010 
-- Design Name: 
-- Module Name:    registro IF_ID - Behavioral 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RegIF_ID is
    Port ( CLK : in  STD_LOGIC;
           DATA1 : in  STD_LOGIC_VECTOR (31 downto 0);
			  DATA2 : in  STD_LOGIC_VECTOR (15 downto 0);
           SAL1 : out  STD_LOGIC_VECTOR (31 downto 0);
			  SAL2 : out  STD_LOGIC_VECTOR (15 downto 0));
end RegIF_ID;

architecture Behavioral of RegIF_ID is
signal Q1int: std_logic_vector(31 downto 0):= (others => '0');
signal Q2int: std_logic_vector(15 downto 0):= (others => '0');
begin

	process (CLK)
		begin

		if falling_edge(CLK) then
			Q1int <= DATA1;
			Q2int <= DATA2;
		end if;

	end process;
SAL1 <= Q1int;
SAL2 <= Q2int;

end Behavioral;