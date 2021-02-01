`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/05/2017 09:07:31 AM
// Design Name: 
// Module Name: 7Segment
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


module SevenSegment(
 input clock,
 input [3:0]FreqState,
output a, b, c, d, e, f, g, dp, //the individual LED output for the seven segment along with the digital point
output [3:0] an   // the 4 bit enable signal
);

reg [3:0]in0;
reg [3:0]in1;
reg [3:0]in2;
reg [3:0]in3;
reg tempdp;
localparam N = 18;

reg [N-1:0]count; //the 18 bit counter which allows us to multiplex at 1000Hz
initial begin
in0<=0;
in1<=0;
in2<=0;
in3<=0;
end
always @ (posedge clock)
begin
  count <= count + 1;
end

reg [6:0]sseg; //the 7 bit register to hold the data to output
reg [3:0]an_temp; //register for the 4 bit enable

always @ (*)
begin
 case(count[N-1:N-2]) //using only the 2 MSB's of the counter 
   
  2'b00 :  //When the 2 MSB's are 00 enable the fourth display
   begin
    sseg <= in0;
    tempdp <= 1;
    an_temp <= 4'b1110;
   end
   
  2'b01:  //When the 2 MSB's are 01 enable the third display
   begin
    sseg <= in1;
    tempdp <= 1;
    an_temp <= 4'b1101;
   end
   
  2'b10:  //When the 2 MSB's are 10 enable the second display
   begin
    sseg <= in2;
    tempdp <= 0;
    an_temp <= 4'b1011;
   end
    
  2'b11:  //When the 2 MSB's are 11 enable the first display
   begin
    sseg <= in3;
    tempdp <= 1;
    an_temp <= 4'b0111;
   end
 endcase
end
assign an = an_temp;


reg [6:0] sseg_temp; // 7 bit register to hold the binary value of each input given

always @ (*)
begin
 case(sseg)
  4'd0 : sseg_temp <= 7'b1000000; //to display 0
  4'd1 : sseg_temp <= 7'b1111001; //to display 1
  4'd2 : sseg_temp <= 7'b0100100; //to display 2
  4'd3 : sseg_temp <= 7'b0110000; //to display 3
  4'd4 : sseg_temp <= 7'b0011001; //to display 4
  4'd5 : sseg_temp <= 7'b0010010; //to display 5
  4'd6 : sseg_temp <= 7'b0000010; //to display 6
  4'd7 : sseg_temp <= 7'b1111000; //to display 7
  4'd8 : sseg_temp <= 7'b0000000; //to display 8
  4'd9 : sseg_temp <= 7'b0010000; //to display 9
  default : sseg_temp <= 7'b0111111; //dash
 endcase
end
always @ (*)
begin
 case(FreqState)
  4'd0 : begin in0<=12;in1<=12;in2<=12;in3<=12; end
  4'd7 : begin in0<=0;in1<=0;in2<=7;in3<=0; end
  4'd8 : begin in0<=0;in1<=0;in2<=8;in3<=0; end
  4'd9 : begin in0<=0;in1<=0;in2<=9;in3<=0; end
  4'd10 :  begin in0<=0;in1<=0;in2<=0;in3<=1; end
  4'd11 :  begin in0<=0;in1<=0;in2<=1;in3<=1; end
  4'd12 :  begin in0<=0;in1<=0;in2<=2;in3<=1; end
  4'd13 :  begin in0<=0;in1<=0;in2<=3;in3<=1; end
  4'd14 :  begin in0<=0;in1<=0;in2<=4;in3<=1; end
  default : begin in0<=0;in1<=0;in2<=0;in3<=0; end
 endcase
end

assign {g, f, e, d, c, b, a} = sseg_temp; //concatenate the outputs to the register, this is just a more neat way of doing this.
// I could have done in the case statement: 4'd0 : {g, f, e, d, c, b, a} = 7'b1000000; 
// its the same thing.. write however you like it

assign dp = tempdp; //since the decimal point is not needed, all 4 of them are turned off


endmodule

