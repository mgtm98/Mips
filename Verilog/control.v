module Control(OpCode, RegDest, Branch, MemRead, MemToReg, ALUOp, MemWrite, ALUSrc, RegWrite, Jump);
	input [5:0] OpCode;
	output reg RegDest, Branch, MemRead, MemToReg, MemWrite, ALUSrc, RegWrite, Jump;
	output reg [2:0]ALUOp;
	
	always @(OpCode)
	begin
		if(OpCode == 10)       // OpCode of R type
		begin
			{Branch, MemRead, MemWrite, ALUSrc, RegWrite, Jump}
			<= 000010;
			MemToReg = 2'b00;
			RegDest = 2'b01;
			ALUOp = 3'b000;
		end
		else if(OpCode == 15) // OpCode of the LW
		begin
			{ Branch, MemRead, MemWrite, ALUSrc, RegWrite, Jump}
			<= 010110;
			MemToReg =2'b01;
			RegDest =2'b00;
			ALUOp = 3'b010;
		end
		else if(OpCode == 43) // OpCode of the SW
		begin
			{Branch, MemRead, MemWrite, ALUSrc, RegWrite, Jump}
			<= 001100; // RegDest and MemToReg are dont cares
			RegDest = 2'bxx;
			MemToReg = 2'bxx;
			ALUOp = 3'b010;
		end
		else if(OpCode == 4) // OpCode of the beq
		begin
			{Branch, MemRead, MemWrite, ALUSrc, RegWrite, Jump}
			<= 100000; // RegDest and MemToReg are dont cares
			RegDest = 2'bxx;
			MemToReg = 2'bxx;
			ALUOp = 3'b110;
		end
		else if (OpCode ==2) // opcode of the jump 
		begin
			{MemRead, MemWrite, RegWrite, Jump}
			<= 0001;
			ALUSrc =1'bx;
			Branch = 1'bx;
			RegDest=2'bxx;
			MemToReg= 2'bxx;
			ALUOp = 3'bxxx;
		end
		else if (OpCode == 7)
		begin
			{ MemRead, MemWrite, RegWrite, Jump} <= 0011;
			Branch = 1'bx;
			ALUSrc =1'bx;
			RegDest=2'b10;	
			MemToReg= 2'b10;
			ALUOp = 3'bxxx;
		end

	end
endmodule
