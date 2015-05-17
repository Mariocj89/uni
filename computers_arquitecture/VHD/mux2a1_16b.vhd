----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:43:31 10/23/2010 
-- Design Name: 
-- Module Name:    mux2a1_16b - Behavioral 
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

entity mux2a1_16b is
    Port ( D0 : in  STD_LOGIC_VECTOR (15 downto 0);
           D1 : in  STD_LOGIC_VECTOR (15 downto 0);
           Sel : in  STD_LOGIC;
           F : out  STD_LOGIC_VECTOR (15 downto 0));
end mux2a1_16b;

architecture Behavioral of mux2a1_16b is

begin

process(D0,D1,Sel)
begin
		if Sel = '0' then
			F <= D0;
		else
			F <= D1;
		end if;

end process;

end Behavioral;

