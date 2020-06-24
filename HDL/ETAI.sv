// Error Tolerant Adder Type I

// helper module, used in approximate region
module LOXOR (
    input  logic a,
    input  logic b,
    input  logic andprev,

    output logic s,
    output logic andout
);
    assign andout = (a & b) | andprev ;
    assign s      = (a | b) | andprev ;
    
endmodule


module ETAI #(
    parameter BITWIDTH = 8,
    parameter BORDER   = 2,
    parameter SUBTYPE  = 1
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,

    output logic [BITWIDTH:0] sum
);

    // Approximate region
    logic  andcarry [BORDER:0];
    assign andcarry[BORDER] = 0; 

    generate;
        for (genvar i = BORDER-1; i >= 0; i--) begin : la_genapprox
            LOXOR loxor (
                .a       ( a[i]          ),
                .b       ( b[i]          ),
                .s       ( sum[i]        ),
                .andprev ( andcarry[i+1] ),
                .andout  ( andcarry[i]   )
            );
        end
    endgenerate

    // Accurate region
    generate;
        if (SUBTYPE == 0) begin
            RCA #( .BITWIDTH ( BITWIDTH - BORDER ) ) rca (
                .a   ( a[BITWIDTH-1 : BORDER] ),
                .b   ( b[BITWIDTH-1 : BORDER] ),
                .cin ( 1'b0                   ), 
                .sum ( sum[BITWIDTH : BORDER] )
            );
        end else begin
            CLA #( .BITWIDTH (BITWIDTH - BORDER )) cla (
                .a   ( a[BITWIDTH-1 : BORDER] ),
                .b   ( b[BITWIDTH-1 : BORDER] ),
                .cin ( 1'b0                   ), 
                .sum ( sum[BITWIDTH : BORDER] )
            );
        end
    endgenerate

endmodule