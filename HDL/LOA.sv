// Lower-part OR Adder

module LOA #(
    parameter BITWIDTH = 8,
    parameter BORDER   = 2,
    parameter SUBTYPE  = 1
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,

    output logic [BITWIDTH:0] sum
);
    
    // Approximate region
    generate;
        for (genvar i = 0; i < BORDER; i++) begin : la_genapprox
            assign sum[i] = a[i] | b[i];
        end
    endgenerate

    // Accurate region
    generate;
        if (SUBTYPE == 0) begin
            RCA #( .BITWIDTH ( BITWIDTH - BORDER ) ) rca (
                .a   ( a[BITWIDTH-1 : BORDER]    ),
                .b   ( b[BITWIDTH-1 : BORDER]    ),
                .cin ( a[BORDER-1] & b[BORDER-1] ), 
                .sum ( sum[BITWIDTH : BORDER]    )
            );
        end else begin
            CLA #( .BITWIDTH (BITWIDTH - BORDER )) cla (
                .a   ( a[BITWIDTH-1 : BORDER]    ),
                .b   ( b[BITWIDTH-1 : BORDER]    ),
                .cin ( a[BORDER-1] & b[BORDER-1] ), 
                .sum ( sum[BITWIDTH : BORDER]    )
            );
        end
    endgenerate

endmodule