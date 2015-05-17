----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:16:46 11/11/2010 
-- Design Name: 
-- Module Name:    Alu_control - Behavioral 
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

entity Alu_control is
    Port ( aluOp : in  STD_LOGIC_VECTOR (1 downto 0);
           funcion : in  STD_LOGIC_VECTOR (5 downto 0);
           alu_fun : out  STD_LOGIC_VECTOR (2 downto 0));
end Alu_control;


architecture Behavioral of Alu_control is
signal sel : STD_LOGIC_VECTOR(7 downto 0);
begin
		sel <= aluOp & funcion;
		alu_fun <= "010" when sel(7 downto 6) = "00" else
					  "001" when sel(7 downto 6) = "11" else
					  "111" when sel(7 downto 6) = "01" else
					  "010" when sel = "10100000" else
					  "110" when sel = "10100010" else
					  "111" when sel = "10101010" else
					  "000" when sel = "10100100" else
					  "001" when sel = "10100101" else
					  "011" when sel = "10100110" else
					  "100" when sel = "10100111";
	
end Behavioral;

