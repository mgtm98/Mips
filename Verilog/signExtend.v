module SignExtend(result,in);
    input [15:0] in;
    output [31:0] result;
    assign result = {{16{in[15]}}, in};
endmodule