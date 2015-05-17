----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:31:09 11/11/2010 
-- Design Name: 
-- Module Name:    u_control - Behavioral 
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

entity u_control is
    Port ( codop : in  STD_LOGIC_VECTOR (5 downto 0);
           fr : in  STD_LOGIC_VECTOR (1 downto 0);
           sal : out  STD_LOGIC_VECTOR (14 downto 0));
end u_control;

architecture Behavioral of u_control is

signal outR: STD_LOGIC_VECTOR (14 downto 0);
begin

	outR <= "000000101000001" when fr = "01" else
			  "011000001000000" when fr = "10" else
			  "000000000000000";
			  
	with codop select
	sal <= outR when "000000",
			 "000000000010001" when "001000",
			 "000000001010001" when "001101",--aqui creo que cambiamos ya esta cambiado
			 "000000000010011" when "100011",
			 "000000000011000" when "101011",
			 "010100000000000" when "000010",
			 "010101010000101" when "000011",
			 "010000000000000" when "000100",
			 "010010000000000" when "000101",
			 "000000000110001" when "001010",
			 "000000000000000" when OTHERS;
			 
end Behavioral;

