`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/05/2017 07:25:14 PM
// Design Name: 
// Module Name: LEDs
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


module LEDs(
input clk,
input [3:0]FreqState,
output RED,
output GREEN,
output BLUE
    );
reg tempRED;
reg tempGREEN;
reg tempBLUE;
reg [24:0]ToggleCounter;

initial begin
tempRED <=0;
tempGREEN <=0;
tempBLUE <=0;
end
always@(posedge clk) begin
ToggleCounter<=ToggleCounter+1;

if (ToggleCounter==0)
begin
    if (FreqState==9)
    begin
    tempBLUE<=~tempBLUE;
    tempGREEN<=0;
    tempRED<=0;
    end
    else if (FreqState==10)
    begin
    tempBLUE<=0;
    tempGREEN<=0;
    tempRED<=~tempRED;
    end
    else if (FreqState==11)
    begin
    tempBLUE<=0;
    tempGREEN<=~tempGREEN;
    tempRED<=0;
    end
    else
    begin
    tempBLUE<=0;
    tempGREEN<=0;
    tempRED<=0;
    end
end
end

assign RED = tempRED;
assign BLUE = tempBLUE;
assign GREEN = tempGREEN;


endmodule
