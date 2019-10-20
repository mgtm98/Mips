module adder_32(sum,cout,num1,num2,cin);
    output wire [31:0] sum;
    output wire cout;
    input wire [31:0] num1;
    input wire [31:0] num2;
    input wire cin;
    wire [32:0] c;
    assign c[0] = cin;
    assign cout = c[32];
    adder add [31:0] (sum[31:0],c[32:1],num1[31:0],num2[31:0],c[31:0]);
endmodule


module adder(sum,cout,num1,num2,cin);
    output wire sum, cout;
    input wire num1, num2, cin;
    wire w1,w2,w3;
    xor(w1,num1,num2);
    xor(sum,w1,cin);
    and(w2,w1,cin);
    and(w3,num1,num2);
    or(cout,w2,w3);
endmodule

module adder_32TB();
    reg [31:0] a; 
    reg [31:0] b;
    wire [31:0] sum;
    wire cout;
    adder_32 add (sum,cout,a,b,0);
    initial begin
        $monitor("%d + %d = %d",a,b,sum);
        a <= 2;
        b <= 7;
	#2
	a <= 15;
	b <= 1825;
    end   
endmodule