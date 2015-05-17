----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:26:58 11/10/2010 
-- Design Name: 
-- Module Name:    procesador - Behavioral 
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

entity procesador is
    Port ( CLK : in  STD_LOGIC);
end procesador;

architecture Behavioral of procesador is
--declarar señales internas señales const
signal instruc: STD_LOGIC_VECTOR (31 downto 0);
signal salPC: STD_LOGIC_VECTOR (15 downto 0);
signal salPC4: STD_LOGIC_VECTOR (15 downto 0);
signal nextpc: STD_LOGIC_VECTOR (15 downto 0);
signal nextpc2: STD_LOGIC_VECTOR (15 downto 0);
signal tr: STD_LOGIC_VECTOR (1 downto 0);
signal sal_control: STD_LOGIC_VECTOR (14 downto 0);
signal ALUfunc: STD_LOGIC_VECTOR (2 downto 0);
signal DataEsc: STD_LOGIC_VECTOR (15 downto 0);
signal A: STD_LOGIC_VECTOR (15 downto 0) ;
signal B: STD_LOGIC_VECTOR (15 downto 0) ;
signal Inm_pc4: STD_LOGIC_VECTOR (15 downto 0);
signal dirwreg: STD_LOGIC_VECTOR (4 downto 0);
signal ALUb: STD_LOGIC_VECTOR (15 downto 0);
signal zflag: STD_LOGIC;
signal ALUres: STD_LOGIC_VECTOR (15 downto 0);
signal pc4orALU: STD_LOGIC_VECTOR (15 downto 0);
signal Salmemdat: STD_LOGIC_VECTOR (15 downto 0);

signal ID_instruc: STD_LOGIC_VECTOR (31 downto 0);
signal ID_pc4: STD_LOGIC_VECTOR (15 downto 0);

signal EX_g3: STD_LOGIC_VECTOR(1 downto 0);
signal EX_g2: STD_LOGIC_VECTOR(1 downto 0);
signal EX_a: STD_LOGIC_VECTOR(15 downto 0);
signal EX_b: STD_LOGIC_VECTOR(15 downto 0);
signal EX_inm_pc4: STD_LOGIC_VECTOR (15 downto 0);
signal EX_dirwreg: STD_LOGIC_VECTOR (4 downto 0);
signal EX_ALUfunc: STD_LOGIC_VECTOR (2 downto 0);
signal EX_ALUSrcB: STD_LOGIC;

signal MEM_g3: STD_LOGIC_VECTOR(1 downto 0);
signal MEM_g2: STD_LOGIC_VECTOR(1 downto 0);
signal MEM_aluresult: STD_LOGIC_VECTOR(15 downto 0);
signal MEM_b: STD_LOGIC_VECTOR(15 downto 0);
signal MEM_inm_pc4: STD_LOGIC_VECTOR (15 downto 0);
signal MEM_dirwreg: STD_LOGIC_VECTOR (4 downto 0);

signal WB_dirwreg: STD_LOGIC_VECTOR (4 downto 0);
signal WB_pc4orALU: STD_LOGIC_VECTOR (15 downto 0);
signal WB_g3: STD_LOGIC_VECTOR(1 downto 0);
signal WB_Salmemdat: STD_LOGIC_VECTOR (15 downto 0);

--declarar alias
alias dirminst: STD_LOGIC_VECTOR (7 downto 0) is salPC (7 downto 0);
alias codop: STD_LOGIC_VECTOR (5 downto 0) is ID_instruc (31 downto 26);
alias funcion: STD_LOGIC_VECTOR (5 downto 0) is ID_instruc (5 downto 0);
alias aluop: STD_LOGIC_VECTOR (1 downto 0) is sal_control (6 downto 5);
alias rs: STD_LOGIC_VECTOR (4 downto 0) is ID_instruc (25 downto 21);
alias rt: STD_LOGIC_VECTOR (4 downto 0) is ID_instruc (20 downto 16);
alias rd: STD_LOGIC_VECTOR (4 downto 0) is ID_instruc (15 downto 11);
alias dir_inm: STD_LOGIC_VECTOR (15 downto 0) is ID_instruc (15 downto 0);
alias PCoDir: STD_LOGIC is sal_control (7);
alias RegDst: STD_LOGIC_VECTOR (1 downto 0) is sal_control (9 downto 8);
alias g2: STD_LOGIC_VECTOR (1 downto 0) is sal_control (3 downto 2);
alias g3: STD_LOGIC_VECTOR (1 downto 0) is sal_control (1 downto 0);
alias ALUSrcB: STD_LOGIC is sal_control (4);
alias PCtoReg: STD_LOGIC is MEM_g2 (0);
alias MemWrite: STD_LOGIC is MEM_g2 (1);
alias RegWrite: STD_LOGIC is WB_g3 (0);
alias MemtoReg: STD_LOGIC is WB_g3 (1);
alias NoSecu: STD_LOGIC is sal_control(13);
alias TipoBR: STD_LOGIC is sal_control(10);
alias PCSrc: STD_LOGIC_VECTOR(1 downto 0) is sal_control(12 downto 11);
alias dir_mem: STD_LOGIC_VECTOR(7 downto 0) is MEM_aluresult(8 downto 1);

--declarar componentes
	COMPONENT mem_inst
	PORT(
		dir : IN std_logic_vector(7 downto 0);          
		dout : OUT std_logic_vector(31 downto 0)
		);
	END COMPONENT;
	
	COMPONENT reregistroPC
	PORT(
		CLK : IN std_logic;
		DATA : IN std_logic_vector(15 downto 0);          
		PC : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;
	
	COMPONENT RegIF_ID
	PORT(
		CLK : IN std_logic;
		DATA1 : IN std_logic_vector(31 downto 0);
		DATA2 : IN std_logic_vector(15 downto 0);          
		SAL1 : OUT std_logic_vector(31 downto 0);
		SAL2 : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;

	COMPONENT dtr
	PORT(
		d_in : IN std_logic_vector(5 downto 0);          
		d_out : OUT std_logic_vector(1 downto 0)
		);
	END COMPONENT;
	
	COMPONENT u_control
	PORT(
		codop : IN std_logic_vector(5 downto 0);
		fr : IN std_logic_vector(1 downto 0);          
		sal : OUT std_logic_vector(14 downto 0)
		);
	END COMPONENT;
	
	COMPONENT Alu_control
	PORT(
		aluOp : IN std_logic_vector(1 downto 0);
		funcion : IN std_logic_vector(5 downto 0);          
		alu_fun : OUT std_logic_vector(2 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT Breg_4p
	PORT(
		clk : IN std_logic;
		regwrite : IN std_logic;
		DirEsc : IN std_logic_vector(4 downto 0);
		DataEsc : IN std_logic_vector(15 downto 0);
		DirLecA : IN std_logic_vector(4 downto 0);
		DirLecB : IN std_logic_vector(4 downto 0);          
		DataLeA : OUT std_logic_vector(15 downto 0);
		DataLeB : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;
	
	COMPONENT mux2a1_16b
	PORT(
		D0 : IN std_logic_vector(15 downto 0);
		D1 : IN std_logic_vector(15 downto 0);
		Sel : IN std_logic;          
		F : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT mux3a1_5b
	PORT(
		D0 : IN std_logic_vector(4 downto 0);
		D1 : IN std_logic_vector(4 downto 0);
		D2 : IN std_logic_vector(4 downto 0);
		Sel : IN std_logic_vector(1 downto 0);          
		F : OUT std_logic_vector(4 downto 0)
		);
	END COMPONENT;
	
	COMPONENT RegID_EX
	PORT(
		CLK : IN std_logic;
		DATA1 : IN std_logic_vector(15 downto 0);
		DATA2 : IN std_logic_vector(15 downto 0);
		DATA3 : IN std_logic_vector(15 downto 0);
		DATA4 : IN std_logic_vector(4 downto 0);
		DATA5 : IN std_logic_vector(1 downto 0);
		DATA6 : IN std_logic_vector(1 downto 0);
		DATA7 : IN std_logic;
		DATA8 : IN std_logic_vector(2 downto 0);          
		SAL1 : OUT std_logic_vector(15 downto 0);
		SAL2 : OUT std_logic_vector(15 downto 0);
		SAL3 : OUT std_logic_vector(15 downto 0);
		SAL4 : OUT std_logic_vector(4 downto 0);
		SAL5 : OUT std_logic_vector(1 downto 0);
		SAL6 : OUT std_logic_vector(1 downto 0);
		SAL7 : OUT std_logic;
		SAL8 : OUT std_logic_vector(2 downto 0)
		);
	END COMPONENT;
	
	COMPONENT Alu16
	PORT(
		A : IN std_logic_vector(15 downto 0);
		B : IN std_logic_vector(15 downto 0);
		con : IN std_logic_vector(2 downto 0);          
		z : OUT std_logic;
		res : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT RegEX_MEM
	PORT(
		CLK : IN std_logic;
		DATA1 : IN std_logic_vector(15 downto 0);
		DATA2 : IN std_logic_vector(15 downto 0);
		DATA3 : IN std_logic_vector(15 downto 0);
		DATA4 : IN std_logic_vector(4 downto 0);
		DATA5 : IN std_logic_vector(1 downto 0);
		DATA6 : IN std_logic_vector(1 downto 0);          
		SAL1 : OUT std_logic_vector(15 downto 0);
		SAL2 : OUT std_logic_vector(15 downto 0);
		SAL3 : OUT std_logic_vector(15 downto 0);
		SAL4 : OUT std_logic_vector(4 downto 0);
		SAL5 : OUT std_logic_vector(1 downto 0);
		SAL6 : OUT std_logic_vector(1 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT mem_data
	PORT(
		WE : IN std_logic;
		CLK : IN std_logic;
		ADDR : IN std_logic_vector(7 downto 0);
		DATAin : IN std_logic_vector(15 downto 0);          
		DATAOUT : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT RegMEM_WB
	PORT(
		CLK : IN std_logic;
		DATA1 : IN std_logic_vector(15 downto 0);
		DATA3 : IN std_logic_vector(15 downto 0);
		DATA4 : IN std_logic_vector(4 downto 0);
		DATA5 : IN std_logic_vector(1 downto 0);          
		SAL1 : OUT std_logic_vector(15 downto 0);
		SAL3 : OUT std_logic_vector(15 downto 0);
		SAL4 : OUT std_logic_vector(4 downto 0);
		SAL5 : OUT std_logic_vector(1 downto 0)
		);
	END COMPONENT;	
	
	COMPONENT salto_control
	PORT(
		PCsrc : IN std_logic_vector(1 downto 0);
		TipoBr : IN std_logic;
		rs : IN std_logic_vector(15 downto 0);
		rt : IN std_logic_vector(15 downto 0);
		pc4 : IN std_logic_vector(15 downto 0);
		dir : IN std_logic_vector(15 downto 0);          
		nextpc : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;	
	
	
begin
--sentencias asignacion de señal concurrentes
	salPC4 <= salPC +4;
--sentencias de instanciación de componentes
	Inst_mem_inst: mem_inst PORT MAP(
		dir => dirminst,
		dout => instruc
	);
	
	Inst_reregistroPC: reregistroPC PORT MAP(
		CLK => CLK,
		DATA => nextpc2,
		PC => salpc
	);	

	Inst_RegIF_ID: RegIF_ID PORT MAP(
		CLK => CLK,
		DATA1 => instruc,
		DATA2 => salPC4,
		SAL1 => ID_instruc,
		SAL2 => ID_pc4
	);

	Inst_dtr: dtr PORT MAP(
		d_in => funcion,
		d_out => tr
	);
	
	Inst_u_control: u_control PORT MAP(
		codop => codop,
		fr => tr,
		sal => sal_control
	);	
	
	Inst_Alu_control: Alu_control PORT MAP(
		aluOp => aluop,
		funcion => funcion,
		alu_fun => ALUfunc
	);
	
	Inst_Breg_4p: Breg_4p PORT MAP(
		clk => CLK,
		regwrite => RegWrite,
		DirEsc => WB_dirWreg,
		DataEsc => DataEsc,
		DirLecA => rs,
		DirLecB => rt,
		DataLeA => A,
		DataLeB => B
	);
	
	Inst1_mux2a1_16b: mux2a1_16b PORT MAP(
		D0 => dir_inm,
		D1 => ID_pc4,
		Sel => PCoDir,
		F => Inm_pc4
	);	

	Inst1_mux3a1_5b: mux3a1_5b PORT MAP(
		D0 => rt,
		D1 => rd,
		D2 => "01111",
		Sel => RegDst,
		F => dirwreg
	);
	
	Inst_RegID_EX: RegID_EX PORT MAP(
		CLK => CLK,
		DATA1 => A,
		DATA2 => B,
		DATA3 => Inm_pc4,
		DATA4 => dirwreg,
		DATA5 => g3,
		DATA6 => g2,
		DATA7 => ALUSrcB,
		DATA8 => ALUfunc,
		SAL1 => EX_a,
		SAL2 => EX_b,
		SAL3 => EX_inm_pc4,
		SAL4 => EX_dirwreg,
		SAL5 => EX_g3,
		SAL6 => EX_g2,
		SAL7 => EX_ALUSrcB,
		SAL8 => EX_ALUfunc
	);	
	
	Inst2_mux2a1_16b: mux2a1_16b PORT MAP(
		D0 => EX_b,
		D1 => EX_inm_pc4,
		Sel => EX_ALUSrcB,
		F => ALUb
	);		
	
	Inst_Alu16: Alu16 PORT MAP(
		A => EX_a,
		B => ALUb,
		con => EX_ALUfunc,
		z => zflag,
		res => ALUres
	);	

	Inst_RegEX_MEM: RegEX_MEM PORT MAP(
		CLK => CLK,
		DATA1 => ALUres,
		DATA2 => EX_b,
		DATA3 => EX_inm_pc4,
		DATA4 => EX_dirwreg,
		DATA5 => EX_g3,
		DATA6 => EX_g2,
		SAL1 => MEM_aluresult,
		SAL2 => MEM_b,
		SAL3 => MEM_inm_pc4,
		SAL4 => MEM_dirwreg,
		SAL5 => MEM_g3,
		SAL6 => MEM_g2
	);	
	
	Inst3_mux2a1_16b: mux2a1_16b PORT MAP(
		D0 => MEM_aluresult,
		D1 => MEM_inm_pc4,
		Sel => PCtoReg,
		F => pc4orALU
	);	
	
	Inst_mem_data: mem_data PORT MAP(
		WE => MemWrite,
		CLK => CLK,
		ADDR => dir_mem, --Alias de MEM_aluresult
		DATAin => MEM_b,
		DATAOUT => Salmemdat
	);	

	Inst_RegMEM_WB: RegMEM_WB PORT MAP(
		CLK => CLK,
		DATA1 => Salmemdat,
		DATA3 => pc4orALU,
		DATA4 => MEM_dirwreg,
		DATA5 => MEM_g3,
		SAL1 => WB_Salmemdat,
		SAL3 => WB_pc4orALU,
		SAL4 => WB_dirwreg,
		SAL5 => WB_g3
	);
	
	Inst4_mux2a1_16b: mux2a1_16b PORT MAP(
		D0 => WB_pc4orALU,
		D1 => WB_Salmemdat,
		Sel => MemtoReg,
		F => DataEsc
	);	
	
	Inst5_mux2a1_16b: mux2a1_16b PORT MAP(
		D0 => salpc4,
		D1 => nextpc,
		Sel => NoSecu,
		F => nextpc2
	);	
	
	Inst_salto_control: salto_control PORT MAP(
		PCsrc => PCSrc,
		TipoBr => TipoBR,
		rs => A,
		rt => B,
		pc4 => ID_pc4,
		dir => dir_inm,
		nextpc => nextpc
	);	

end Behavioral;

