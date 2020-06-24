// Carry-Lookahead Adder

// Sum Propagate Generate full-adder cell
module SPG (
    input  logic a,
    input  logic b,
    input  logic cin,
    output logic s,
    output logic p,
    output logic g
);
    assign g = a & b   ;
    assign p = a ^ b   ;
    assign s = p ^ cin ;
endmodule

// 4-bit Look-ahead Carry Unit
module LCU (
    input  logic       cin,
    input  logic [3:0] gin,
    input  logic [3:0] pin,
    output logic [4:1] cout
);
    assign cout[1] = gin[0] | (pin[0] & cin);
    assign cout[2] = gin[1] | (pin[1] & cout[1]);
    assign cout[3] = gin[2] | (pin[2] & cout[2]);
    assign cout[4] = gin[3] | (pin[3] & cout[3]);
endmodule


module CLA #(
    parameter BITWIDTH = 8
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,
    input  logic                cin,

    output logic [BITWIDTH:0] sum
);
    logic [BITWIDTH-1:0] gins;
    logic [BITWIDTH-1:0] pins;
    logic [BITWIDTH:0]   carry;

    assign carry[0] = cin;

   generate;
        for (genvar i = 0; i < BITWIDTH-1; i += 4) begin : la_gen_lcus
            LCU lcu (                      // i = 0,      i = 4
                .cin  ( carry[i]        ), // carry[0],   carry[4]
                .gin  ( gins [i   +: 4] ), // gins [3:0], gins [7:4]
                .pin  ( pins [i   +: 4] ), // pins [3:0], pins [7:4]
                .cout ( carry[i+1 +: 4] )  // carry[4:1], carry[8:5]
            );
        end 
    endgenerate

    generate;
        for (genvar i = 0; i < BITWIDTH; i++) begin : la_gen_spgs
            SPG spg (
                .a   ( a[i]     ),
                .b   ( b[i]     ),
                .cin ( carry[i] ),
                .s   ( sum[i]   ),
                .p   ( pins[i]  ),
                .g   ( gins[i]  )
            );
        end
    endgenerate

    assign sum[BITWIDTH] = carry[BITWIDTH];
    
endmodule