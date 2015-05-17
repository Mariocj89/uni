----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:41:51 10/20/2010 
-- Design Name: 
-- Module Name:    Alu16 - Behavioral 
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

entity Alu16 is
    Port ( A : in  STD_LOGIC_VECTOR (15 downto 0);
           B : in  STD_LOGIC_VECTOR (15 downto 0);
           con : in  STD_LOGIC_VECTOR (2 downto 0);
           z : out  STD_LOGIC;
           res : out  STD_LOGIC_VECTOR (15 downto 0));
end Alu16;

architecture Behavioral of Alu16 is

signal R: std_logic_vector(15 downto 0);
begin
process (A, B, con)
begin
case con is
when "000" =>
R <= (A and B);
when "001" =>
R <= (A or B);
when "010" =>
R <= (A + B);
when "011" =>
R <= (A xor B);
when "100" =>
R <= (A nor B);
when "110" =>
R <= (A - B);
when "111" =>
if (A < B) then
R <= X"0001";
else
R <= X"0000";
end if;
when others => null;
end case;
end process;
Res <= R;
z <= '1' when R = X"0000" else '0';


end Behavioral;

