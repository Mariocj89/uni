----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:05:00 10/07/2010 
-- Design Name: 
-- Module Name:    reregistroPC - Behavioral 
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

entity reregistroPC is
    Port ( CLK : in  STD_LOGIC;
           DATA : in  STD_LOGIC_VECTOR (15 downto 0);
           PC : out  STD_LOGIC_VECTOR (15 downto 0));
end reregistroPC;

architecture Behavioral of reregistroPC is
signal Qint: std_logic_vector(15 downto 0):= (others => '0');
begin

	process (CLK)
		begin

		if falling_edge(CLK) then
			Qint <= DATA;
		end if;

	end process;
PC <= Qint;

end Behavioral;

