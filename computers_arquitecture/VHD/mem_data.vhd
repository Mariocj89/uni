-- Nota:
-- Las palabras de memoria han sido ordenadas en sentido ascendente 
-- SE HA AÑADIDO UN PUERTO ADICIONAL DE LECTURA PARA VISUALIZAR UNA
-- POSICION DE MEMORIA Y MOSTRARLA EN LOS LEDS DE LA TARJETA
-- ESTE PUERTO ES INNECESARIO Y SE ACONSEJA ELIMINARLO
------------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all; 
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity mem_data is
port (
WE : in std_logic;
CLK : in std_logic;
ADDR : in std_logic_vector(7 downto 0);
DATAin : in std_logic_vector(15 downto 0);
DATAOUT : out std_logic_vector(15 downto 0));
end entity;

library IEEE;
use IEEE.std_logic_unsigned.all;

architecture ram_arch of mem_data is

type ram_mem_type is array (0 to 255) of std_logic_vector(7 downto 0); 
signal ram_mem : ram_mem_type := (11 => X"0C", 
-- num. de elementos en 10 (ByteH) y 11(ByteL)
12 to 16 => X"ff", -- -1 y -1
17 => X"fe", -- -2
18 => X"ff",
19 => X"fc", -- -4
20 => X"ff", 
21 => X"f8", -- -8
22 => X"ff", 
23 => X"f0", -- -16
24 => X"ff", 
25 => X"e0", -- - 32
26 => X"ff", 
27 => X"c0", -- -64
28 => X"7f", 
29 => X"ff", -- + 32767
30 => X"80",
31 => X"90", -- - 32624
32 => X"00", -- 
33 => X"10", -- +16
34 => X"76", -- 
35 => X"35", -- 30261
others => X"00"); 


begin

process (CLK)
begin
if rising_edge(CLK) then
if (WE = '1') then
ram_mem(CONV_INTEGER(ADDR)) <= DATAin(15 downto 8);
ram_mem(CONV_INTEGER(ADDR + 1)) <= DATAin(7 downto 0);
end if;
end if;
end process;
Dataout <= ram_mem(CONV_INTEGER(ADDR)) & ram_mem(CONV_INTEGER(ADDR + 1));

end architecture;