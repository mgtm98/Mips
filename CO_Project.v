module control(OpCode, RegDest, Branch, MemRead, MemToReg, ALUOp, MemWrite, ALUSrc, RegWrite, Jump);

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


module ALUControl(ALUOp, Func, Sel);

	input [5:0] Func;
	input [2:0] ALUOp;
	output reg [3:0]  Sel;
	always@(ALUOp or Func)
        begin
		if( ALUOp ==3'b000)
		begin
			if(Func ==32) // 32 aad
				Sel = 2;
			else if (Func == 34) // sub
				Sel = 6;
			else if (Func == 36) // and
				Sel = 0;
			else if (Func == 37) // 0r
				Sel = 1;
			else if (Func == 42) // slt
				Sel = 6;
		end

		else if(ALUOp== 3'b010) // lw and sw 
			Sel = 2;
		else if ( ALUOp == 3'b110 ) // branch if equal
			Sel = 6;
	end
	
endmodule


module ALU(A, B, ALUCtrl, ALUOut, Zero);
	input [3:0] ALUCtrl;
	input [31:0] A, B;
	output reg [31:0] ALUOut;
	output Zero;
	
	assign Zero = (ALUOut == 0);
	always @(ALUCtrl, A, B)
	begin
		case(ALUCtrl)
			0: ALUOut <= A & B;
			1: ALUOut <= A | B;
			2: ALUOut <= A + B;
			6: ALUOut <= A - B;
			7: ALUOut <= A < B ? 1 : 0;
			12: ALUOut <= ~(A | B);
			default: ALUOut <= 0; 
		endcase
	end
	

endmodule



