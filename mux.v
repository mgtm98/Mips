module mux_32(out,sel,in1,in2);
    output wire [0:31] out;
    input wire sel;
    input wire [0:31] in1;
    input wire [0:31] in2;
    if (sel)
        out = in2
    else 
        out = in1
endmodule

module mux_5(out,sel,in1,in2);
    output wire [0:4] out;
    input wire sel;
    input wire [0:4] in1;
    input wire [0:4] in2;
    if (sel)
        out = in2
    else 
        out = in1
endmodule