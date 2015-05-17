----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:04:41 11/13/2010 
-- Design Name: 
-- Module Name:    salto_control - Behavioral 
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
use IEEe.NUMERIC_BIT;
use ieee.NUMERIC_STD;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity salto_control is
    Port ( PCsrc : in  STD_LOGIC_VECTOR (1 downto 0);
           TipoBr : in  STD_LOGIC;
           rs : in  STD_LOGIC_VECTOR (15 downto 0);
           rt : in  STD_LOGIC_VECTOR (15 downto 0);
           pc4 : in  STD_LOGIC_VECTOR (15 downto 0);
           dir : in  STD_LOGIC_VECTOR (15 downto 0);
           nextpc : out  STD_LOGIC_VECTOR (15 downto 0));
end salto_control;

architecture Behavioral of salto_control is
signal aux: STD_LOGIC_VECTOR (15 downto 0);
signal zero: STD_LOGIC;
signal igual:BOOLEAN;
signal sel: STD_LOGIC_VECTOR( 1 downto 0);
alias dirdesp: STD_LOGIC_VECTOR (13 downto 0) is dir(13 downto 0);
begin

	zero <= not(TipoBr) when rs = rt else
				TipoBr;


	sel <= "01" when PCsrc = "01" else
				"10" when PCsrc = "10" else
				zero & zero;
	--ASIGNAR A AUX EL VALOR CORRESPONDIENTE
	aux<= (pc4 + (dirdesp & "00"));--desplazar dir 2 a la der
	
	
	with sel select
	nextpc <= pc4 when "00",
		 dir when "01",
		 rs when "10",
		 aux when others;

end Behavioral;

