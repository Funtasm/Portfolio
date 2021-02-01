`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Texas Tech University
// Engineer: Seth Larson
// 
// Create Date: 02/09/2017 07:15:33 PM
// Design Name: 
// Module Name: PWM_Source
// Project Name: Project Lab 1 Final Project
// Target Devices: BASYS3 (xc7a35tcpg236-1)
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments: Vivado Tutorial taught by Daniel Ayada
// 
//////////////////////////////////////////////////////////////////////////////////


module PWM_Source(
    input clk,//defaults to 1 bit binary, on/off.
    input [1:0]speed, //2 bit binary, 4 speeds.
    input reset,
    input ON,
    output PWM
    );
    
    reg [19:0]counter; //reg basically states a variable.
    reg [19:0]width; 
    reg temp_PWM;
    
    initial begin 
    counter <= 0; //non-blocking assesment
    width <= 0;
    temp_PWM <= 0;
    end
    
    always@ ( posedge clk)begin
        if(reset) //if reset is pressed
            counter <=0; //counter reset to 0
        else 
            counter <= counter+1; // otherwise, increment counter.
            
        if((counter<width))
            temp_PWM <= 1; // less than width, outputs 1
        else 
            temp_PWM <=0; //greater than width, outputs 0
     end
     //inside an always@, use non blocking
     //out an always@, can use blocking
     always@(*)begin //update when ANYTHING changes, var change, clock change, etc.
        case(speed) //counts speed amounts and for every value, a assignment is made for width.
            2'd0: width <=20'd0;
            2'd1: width <=20'd400000;
            2'd2: width <=20'd524288;
            2'd3: width <=20'd720000;
        endcase
     end
     
     assign PWM = temp_PWM; //PWM is now equal to the register, and changes with the register.
    
endmodule
