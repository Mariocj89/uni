----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:14:55 11/11/2010 
-- Design Name: 
-- Module Name:    dtr - Behavioral 
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

entity dtr is
    Port ( d_in : in  STD_LOGIC_VECTOR (5 downto 0);
           d_out : out  STD_LOGIC_VECTOR (1 downto 0));
end dtr;

architecture Behavioral of dtr is

begin

	d_out <=	"00" when d_in= "000000" else
				"10" when d_in= "001000" else
				"01" when d_in= "100010" else
				"01"; 

end Behavioral;

