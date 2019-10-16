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