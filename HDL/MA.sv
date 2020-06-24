// Median Adder

module MA #(
    parameter BITWIDTH = 8,
    parameter BORDER   = 2,
    parameter SUBTYPE  = 1
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,

    output logic [BITWIDTH:0] sum
);

    // Approximate region - static median value of dist
    assign sum[BORDER-1] = 0;

    generate;
        for (genvar i = 0; i < BORDER-1; i++) begin : la_gen_approx
            assign sum[i] = 1;
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