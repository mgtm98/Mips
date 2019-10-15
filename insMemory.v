module instMem(insData,pc);
    input wire [14:0] pc;
    output wire [31:0] insData;
    reg [7:0] memory [0:32767];
    assign insData = {memory[pc+3],memory[pc+2],memory[pc+1],memory[pc]};
    initial begin
        $readmemb("/home/mgtm/Verilog/memory.txt",memory);
    end 
endmodule


module instMemTB();
    reg [14:0] pc;
    wire [31:0] insData;
    initial begin
        $display("i am here");
        pc = 0;
        #1000
        pc = 4;
    end 
    instMem mem(insData,pc);
endmodule
