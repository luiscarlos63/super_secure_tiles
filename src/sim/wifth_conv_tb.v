`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/31/2023 09:58:27 AM
// Design Name: 
// Module Name: wifth_conv_tb
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





module width_conv_tb;

  // Parameters
  parameter DATA_WIDTH = 32;
  parameter KEY_WIDTH = 128;

  reg clock;
  reg reset_n;
  
  //Inputs
  reg [DATA_WIDTH-1:0]  key_stream;
  reg                   key_stream_valid;
  

  // Outputs
  wire [KEY_WIDTH-1:0]  key_out;
  wire                  key_ready;

  // Instantiate the module under test
  width_conv  #(KEY_WIDTH) dut(
    .clk(clock),
    .reset_n(reset_n),
    .data(key_stream),
    .data_valid(key_stream_valid),
    .data_ready(key_ready),
    .output_data(key_out)
  );

  // Clock generation
  always begin
    #5 clock = ~clock;
  end

  // Initialize
  initial begin
    clock = 0;
    reset_n = 1;
    key_stream_valid = 0;
    key_stream = 32'hFFFFFFFF;

    // Reset sequence
    reset_n = 0;
    #10 reset_n = 1;

    // Test sequence
    #10 key_stream = 32'hBBBBBBBB;
    key_stream_valid = 1;
    #10 key_stream = 32'h0;
    #10 key_stream = 32'h0;
    #10 key_stream = 32'h0;
    #10 key_stream = 32'h0;
    // Finish simulation
    #10 $finish;
  end

endmodule