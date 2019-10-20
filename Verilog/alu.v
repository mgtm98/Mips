module ALU(A, B, ALUCtrl, ALUOut, Zero);
	input wire [3:0] ALUCtrl;
	input wire [31:0] A;
	input wire [31:0] B;
	output reg [31:0] ALUOut;
	output Zero;
	
	assign Zero = (ALUOut == 0) ? 1 : 0;
	always @(ALUCtrl, A, B)
	begin
		case(ALUCtrl)
			0: 	ALUOut <= A & B;
			1: 	ALUOut <= A | B;
			2: 	ALUOut <= A + B;
			6: 	ALUOut <= A - B;
			7: 	ALUOut <= A < B ? 1 : 0;
			12: ALUOut <= ~(A | B);
			default: ALUOut <= 0; 
		endcase
	end
endmodule



