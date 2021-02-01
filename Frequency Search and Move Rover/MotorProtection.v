`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/05/2017 12:49:57 AM
// Design Name: 
// Module Name: MotorProtection
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


module MotorProtection(
input clk,
input SNSA,
input SNSB,
output ON_CURRENT

    );
    reg tempON;
    reg [24:0]count1;
    reg [24:0]width;
    reg [27:0]count2;
initial begin
tempON<=1;
count1<=0;
count2<=0;
width<=0;
end
 always@(posedge clk)
 begin
   width<=width+1;
      if (SNSA || SNSB)
      begin
        count1<=count1+1;
      end
      if (width==33554431)
      begin
       if (count1>5000000)begin 
     //Approximately 15% of the time.
       tempON<=0;
       end
       else begin
       count1<=0;
       end
      end
      if (~tempON)
      begin
       count2<=count2+1;
       if (count2>100000000)
       begin
        count1<=0;
        tempON<=1;
       end
      end
      else begin
      count2<=0;
      end
    end
assign ON_CURRENT = tempON;
endmodule
