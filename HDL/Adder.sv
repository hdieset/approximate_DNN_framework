module ADDER #(
    parameter ADDERTYPE      = 0,
    parameter SUBADDERTYPE   = 1,
    parameter BITWIDTH       = 8,
    parameter NB_APPROX_BITS = 2
)(
    input  logic [BITWIDTH-1:0] a,
    input  logic [BITWIDTH-1:0] b,

    output logic [BITWIDTH-1:0] sum
);
    logic [BITWIDTH:0] fullSum;

    assign sum = fullSum[BITWIDTH-1:0];

    generate;
        if (ADDERTYPE == 0) begin
            RCA #(.BITWIDTH (BITWIDTH) ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .cin ( 1'b0    ), 
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 1) begin
            CLA #( .BITWIDTH ( BITWIDTH ) ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .cin ( '0      ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 2) begin
            APA #( .BITWIDTH ( BITWIDTH       ),
                   .BORDER   ( NB_APPROX_BITS ),
                   .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 3) begin
            APAII #( .BITWIDTH ( BITWIDTH       ),
                     .BORDER   ( NB_APPROX_BITS ),
                     .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 4) begin
            ETAI #( .BITWIDTH ( BITWIDTH       ), 
                    .BORDER   ( NB_APPROX_BITS ),
                    .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 5) begin
            LOA #( .BITWIDTH ( BITWIDTH       ), 
                   .BORDER   ( NB_APPROX_BITS ),
                   .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 6) begin
            MA #( .BITWIDTH ( BITWIDTH       ), 
                  .BORDER   ( NB_APPROX_BITS ),
                  .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end else if (ADDERTYPE == 7) begin
            TA #( .BITWIDTH ( BITWIDTH       ), 
                  .BORDER   ( NB_APPROX_BITS ),
                  .SUBTYPE  ( SUBADDERTYPE   )
            ) adder (
                .a   ( a       ),
                .b   ( b       ),
                .sum ( fullSum )
            );
        end
    endgenerate
    
endmodule