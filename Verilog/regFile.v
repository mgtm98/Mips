module RegFile(reg1Data,reg2Data,regW,r1A,r2A,wrA,wrD,clk);
    output wire [31:0] reg1Data;    //register 1 Data
    output wire [31:0] reg2Data;    //register 2 Data
    input wire [31:0] wrD;          //write data
    input wire regW;                //register write
    input wire [4:0] r1A;           //register 1 adress
    input wire [4:0] r2A;           //register 2 adress
    input wire [4:0] wrA;           //write register adress
    input wire clk;
    
    reg [31:0] Registers [0:31]; 
    
    assign reg1Data = Registers[r1A];
    assign reg2Data = Registers[r2A];
    
    initial begin
        $readmemb("/home/mgtm/Verilog/reg.txt",Registers);
       $monitor("r1a::%b r2A::%b reg1Data::%b reg2Data::%b",r1A,r2A,reg1Data,reg2Data);
    end 
    
    always @(negedge clk)begin
        if(regW)
            Registers[wrA] = wrD;
    end
endmodule

module regFileTB();
    reg [4:0] wrA = 0;
    reg [4:0] r1A = 1;
    reg [4:0] r2A = 0;
    reg [31:0] wrD ;
    wire [31:0] reg1Data;
    wire [31:0] reg2Data;
    reg regW = 0;
    reg clk = 1;
    RegFile r(reg1Data,reg2Data,regW,r1A,r2A,wrA,wrD,clk);
    initial begin
        wrA = 0;
        wrD = 100;
        regW = 1;
        #10
        regW = 0;
        wrD = 0;
        #10
        regW = 1;
        wrA = 1;
        wrD = 500;
    end
    always begin
        #5
        clk = ~clk;
    end
endmodule