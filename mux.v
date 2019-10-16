module Mux_32(out,sel,in1,in2);
    output reg [0:31] out;
    input wire sel;
    input wire [0:31] in1;
    input wire [0:31] in2;
    always @(sel) begin
        if (sel)
            out = in2;
        else 
            out = in1;
    end
endmodule

module Mux_5(out,sel,in1,in2);
    output reg [0:4] out;
    input wire sel;
    input wire [0:4] in1;
    input wire [0:4] in2;
    always @(sel) begin
        if (sel)
            out = in2;
        else 
            out = in1;
    end
endmodule