`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2017 06:03:56 PM
// Design Name: 
// Module Name: Indu_Sensor
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


module Indu_Sensor(
input clk,
input InductA, InductB,
output ON_INDUCT
    );
//reg [26:0]count_Indu;
//reg Temp_ON_INDUCT;
//reg CountFlagIND;
//reg HomeSigFlag;
//reg Inductive_SNS;
//initial begin
//count_Indu<=0;
//Temp_ON_INDUCT<=1;
//CountFlagIND<=0;
//HomeSigFlag<=0;
//Inductive_SNS<=1;
//end
//always@(posedge clk)
//begin
//if (InductA&&InductB)begin
//Inductive_SNS<=1;end
//else begin
//Inductive_SNS<=0;end
//if (~CountFlagIND) begin
//    if (FreqState ==12 || FreqState ==13) begin//For LED Module use, WIP
//    HomeSigFlag<=1; end
//end
//if (count_Indu==0 && ~Inductive_SNS && ~reset) begin
//Temp_ON_INDUCT <= 0; end
//else if (~Inductive_SNS&&~reset) begin
//Temp_ON_INDUCT<=0;end
//else if (reset && count_Indu ==0) begin
//Temp_ON_INDUCT <=1;
//CountFlagIND <=1; end
//if (CountFlagIND) begin
//count_Indu<=count_Indu+1; end
//if (count_Indu==1000000000) begin
//CountFlagIND<=0;
//count_Indu<=0;end

//end
assign ON_INDUCT = (InductA&&InductB);
endmodule
