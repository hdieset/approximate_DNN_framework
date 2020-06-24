// Ripple Carry Adder

// Full-Adder Cell 
module FA (
    input  logic a,
    input  logic b,
    input  logic cin,

    output logic s,
    output logic cout
);
    logic d;
    assign d = a ^ b; // XOR
    
    assign s = d ^ cin;
    assign cout = (a & b) | (cin & d);

endmodule


module RCA #(
    parameter BITWIDTH = 8
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,
    input  logic                cin,

    output logic [BITWIDTH:0] sum
);

    logic  carry [BITWIDTH:0]; 
    assign carry[0] = cin;

    generate;
        for (genvar i = 0; i < BITWIDTH; i++) begin : la_genblock
            FA fa (
                .a    ( a[i]       ),
                .b    ( b[i]       ),
                .cin  ( carry[i]   ),
                .s    ( sum[i]     ),
                .cout ( carry[i+1] )
            );
        end
    endgenerate

    assign sum[BITWIDTH] = carry[BITWIDTH];
    
endmodule