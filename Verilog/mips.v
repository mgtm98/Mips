module mipsTB();
    reg [14:0] PC = -4;
    wire [31:0] ins;
    wire [5:0] OpCode;
    wire [4:0] rs;
    wire [4:0] rt;
    wire [4:0] rd;
    wire [4:0] shamt;
    wire [5:0] func;
    wire [15:0] imValue;
    wire [25:0] jump_label;
    wire MemToRegControl;
    wire [4:0] writeRegAdress;
    wire [31:0] reg1Data;
    wire [31:0] reg2Data;
    wire [31:0] immediateValue32;
    wire [31:0] in_alu2;
    wire zero;
    wire [31:0] alu_output;
    wire [31:0] data_memory_data;
    wire [31:0] regFile_writeData;
    wire regDstC;
    wire jumpC;
    wire branchC;
    wire memReadC;
    wire memToRegC;
    wire [2:0] aluOpC;
    wire memWriteC;
    wire aluSrcC;
    wire regWriteC;
    wire [3:0] aluControlOutput;
    reg clk = 1;

    ALU alu(reg1Data, in_alu2, aluControlOutput, alu_output, zero);
    ALUControl alu_control(aluOpC, func, aluControlOutput);
    Control controlUnit(OpCode, regDstC, Branch, memReadC, memToRegC, aluOpC, memWriteC, aluSrcC, regWriteC, Jump);
    RegFile regFile(reg1Data,reg2Data,regWriteC,rs,rt,writeRegAdress,regFile_writeData,clk);
    DataMem data_memory(data_memory_data,alu_output,reg2Data,memReadC,memWriteC);
    InstMem insMemory(ins,PC);
    Mux_5 regDist(writeRegAdress,regDstC,rt,rd);
    Mux_32 aluSrc(in_alu2,aluSrcC,reg2Data,immediateValue32);
    Mux_32_2 memToReg(regFile_writeData,memToRegC,alu_output,data_memory_data);
    SignExtend immediateValue(immediateValue32,imValue);
    


    assign OpCode = ins[31:26];
    assign rs = ins[25:21];
    assign rt = ins[20:16];
    assign rd = ins[15:11];
    assign shamt = ins[10:6];
    assign func = ins[5:0];
    assign imValue = {rd,shamt,func};
    assign jump_label = {rs,rt,rd,shamt,func};

    always begin
        #5
        clk = ~clk;
    end

    always @(posedge clk)begin
        PC = PC + 4;
    end

endmodule