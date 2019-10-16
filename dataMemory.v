module DataMem(data,address,wData,read,write);
    output wire [31:0] data;
    input wire [31:0] wData;
    input wire [14:0] address;
    input wire read;
    input wire write;
    reg [7:0] memory [0:32767];
    assign data = (read) ? {memory[address+3],memory[address+2],memory[address+1],memory[address]} : 1'bx;
    always @(write) begin
        if (write)
            memory[address] = wData[7:0];
            memory[address+1] = wData[15:8];
            memory[address+2] = wData[23:16];
            memory[address+3] = wData[31:24];
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
    DataMem mem(insData,pc);
endmodule