`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/31/2023 09:48:43 AM
// Design Name: 
// Module Name: width_conv
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////




module AXI_width_conv
#(
parameter   OUT_WIDTH = 256
)
(
    //slave interface
    input  wire                   s00_axis_aclk,
    input  wire                   s00_axis_aresetn,
    input  wire [32-1:0]  s00_axis_tdata,
    //input  wire [(C_AXIS_TDATA_WIDTH/8)-1 : 0] s00_axis_tstrb,
    input  wire                   s00_axis_tvalid,
    output wire                   s00_axis_tready,
    //input  wire                   s00_axis_tlast,
    
    //output value
    output wire [OUT_WIDTH - 1:0]           output_data
);

width_conv #(OUT_WIDTH)
(
    .clk(s00_axis_aclk),
    .reset_n(s00_axis_aresetn),
    .data(s00_axis_tdata),
    .data_valid(s00_axis_tvalid),
    .data_ready(s00_axis_tready),
    .output_data(output_data)
);


endmodule



module width_conv 
#(
    parameter               OUTPUT_WIDTH = 256
)
(
    input wire              clk,
    input wire              reset_n,
    input wire              data_valid,
    input wire [31:0]       data,
    output wire             data_ready,
    output wire [OUTPUT_WIDTH - 1:0]     output_data
    
);

reg [OUTPUT_WIDTH-1:0] shift_register;

assign output_data = shift_register;

always @(posedge clk) begin
    if (!reset_n) begin
        shift_register <= 0;
                    end else if (data_valid) begin
        shift_register <= {data, shift_register[OUTPUT_WIDTH-1:32]};
    end
end

assign data_ready     = 1;

endmodule