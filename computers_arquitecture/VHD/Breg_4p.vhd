-- PARA 16 registros
-------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;

ENTITY Breg_4p IS
port (
clk : in std_logic;
-- señal para activar escritura
regwrite: in std_logic;
-- dirección de escritura
DirEsc: in std_logic_vector(4 downto 0);
-- Dato de escritura
DataEsc: in std_logic_vector(15 downto 0);	
-- dirección de lectura puerto A
DirLecA: in std_logic_vector(4 downto 0);
-- dirección de lectura puerto B
DirLecB: in std_logic_vector(4 downto 0);
-- dato leido por puerto A
DataLeA: out std_logic_vector(15 downto 0);
-- dato leido por puerto B	
DataLeB: out std_logic_vector(15 downto 0));
End Breg_4p;

ARCHITECTURE compor of Breg_4p is
TYPE breg_tipo IS array(0 to 31) of std_logic_vector(15 downto 0);
SIGNAL breg: breg_tipo:=( 4 => X"0018", 15 => X"22AC", others => X"0000");

BEGIN
  PROCESS (CLK)
  begin
    if clk = '1' and clk'event then  
        -- escritura en registro
        if regwrite = '1' then 
            case DirEsc is
              -- no se escribe en registro 0
              when "00001" => breg(1) <= DataEsc;
              when "00010" => breg(2) <= DataEsc;
              when "00011" => breg(3) <= DataEsc;
              when "00100" => breg(4) <= DataEsc;
              when "00101" => breg(5) <= DataEsc;
              when "00110" => breg(6) <= DataEsc;
              when "00111" => breg(7) <= DataEsc;
				  when "01000" => breg(8) <= DataEsc;
				  when "01001" => breg(9) <= DataEsc;
              when "01010" => breg(10) <= DataEsc;
              when "01011" => breg(11) <= DataEsc;
              when "01100" => breg(12) <= DataEsc;
              when "01101" => breg(13) <= DataEsc;
              when "01110" => breg(14) <= DataEsc;
              when "01111" => breg(15) <= DataEsc;
              when others => null;
            end case;
        end if;
    end if;
  end process;
  
  PROCESS (DirLecA, breg)
    begin
            case DirLecA is
              -- Lectura en el puerto A
              -- implementa mux de 8 a 1
              when "00000" => DataLeA <= breg(0);
              when "00001" => DataLeA <= breg(1);
              when "00010" => DataLeA <= breg(2);
              when "00011" => DataLeA <= breg(3);
              when "00100" => DataLeA <= breg(4);
              when "00101" => DataLeA <= breg(5);
              when "00110" => DataLeA <= breg(6);
              when "00111" => DataLeA <= breg(7);
              when "01000" => DataLeA <= breg(8);
              when "01001" => DataLeA <= breg(9);
              when "01010" => DataLeA <= breg(10);
              when "01011" => DataLeA <= breg(11);
              when "01100" => DataLeA <= breg(12);
              when "01101" => DataLeA <= breg(13);
              when "01110" => DataLeA <= breg(14);
              when "01111" => DataLeA <= breg(15);
              when others => null;
            end case;
  end process;
  
  PROCESS (DirLecB, breg)
    begin
            case DirLecB is
              -- Lectura en el puerto A
              -- implementa mux de 8 a 1
              when "00000" => DataLeB <= breg(0);
              when "00001" => DataLeB <= breg(1);
              when "00010" => DataLeB <= breg(2);
              when "00011" => DataLeB <= breg(3);
              when "00100" => DataLeB <= breg(4);
              when "00101" => DataLeB <= breg(5);
              when "00110" => DataLeB <= breg(6);
              when "00111" => DataLeB <= breg(7);
              when "01000" => DataLeB <= breg(8);
              when "01001" => DataLeB <= breg(9);
              when "01010" => DataLeB <= breg(10);
              when "01011" => DataLeB <= breg(11);
              when "01100" => DataLeB <= breg(12);
              when "01101" => DataLeB <= breg(13);
              when "01110" => DataLeB <= breg(14);
              when "01111" => DataLeB <= breg(15);
              when others => null;
            end case;
  end process;	
END compor;