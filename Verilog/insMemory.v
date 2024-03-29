module InstMem(insData,pc);
    input wire [14:0] pc;
    output wire [31:0] insData;
    reg [7:0] memory [0:32767];
    assign insData = {memory[pc],memory[pc+1],memory[pc+2],memory[pc+3]};
    initial begin
        $readmemb("/home/mgtm/Verilog/memory.txt",memory);
	//$monitor("%b PC::%b",insData,pc);
    end 
endmodule


module instMemTB();
    reg [14:0] pc;
    wire [31:0] insData;
    initial begin
        $display("i am here");
        pc = 0;
        #2
        pc = 4;
    end 
    InstMem mem(insData,pc);
endmodule
