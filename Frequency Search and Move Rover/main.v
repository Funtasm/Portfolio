`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2017 08:27:31 PM
// Design Name: 
// Module Name: TOP_PWM
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


module main(
    input RAW_clk,
    input RAW_SNSA,RAW_SNSB,
    input RAW_reset,ResetLeft,ResetRight,
    input RAW_MicA,RAW_MicB,RAW_MicC,
    input RAW_InductA,RAW_InductB,
    output PWM_L,PWM_R,LED_Forward1,LED_Backwards1,LED_Forward2,LED_Backwards2,LED_PWM_L,LED_PWM_R,
    output RAW_Forward1,RAW_Backwards1, RAW_Forward2,RAW_Backwards2, LED_SNSA,LED_SNSB,
    output a, b, c, d, e, f, g, dp, 
    output [3:0] an,
    output RED,BLUE,GREEN
    );
    wire InductiveSNSFlag;
    wire [1:0]speedL;
    wire [1:0]speedR;
    wire [3:0]FreqState;
  //demo code below, likely to be changed for actual project 
    Motor_Drive MDrive(RAW_clk,RAW_reset,ResetLeft, ResetRight,ON_CURRENT,InductiveSNSFlag,Direction,Rotate,
    Move,FreqState,RAW_Forward1,RAW_Backwards1, RAW_Forward2,RAW_Backwards2,RED,BLUE,GREEN, speedL, speedR);
    PWM_Source LeftLED(RAW_clk,speedL,RAW_reset,InductiveSNSFlag,PWM_L);
    PWM_Source RightLED(RAW_clk,speedR,RAW_reset,InductiveSNSFlag,PWM_R);
    MotorProtection DetectCurrent(RAW_clk,RAW_SNSA,RAW_SNSB,ON_CURRENT);
    //Indu_Sensor InductiveSNS(RAW_clk,RAW_InductA,RAW_InductB,RAW_reset,FreqState,ON_INDUCT);
    Freq_Detector Freq_Detector(RAW_clk,RAW_MicA,FreqState);
    SevenSegment Freq_Display(RAW_clk,FreqState,a, b, c, d, e, f, g, dp,an);
    //LEDs SOS_Signal(RAW_clk,FreqState, RED, GREEN, BLUE);
    Localization Localization(RAW_clk,RAW_MicA,RAW_MicB,Direction,Rotate, Move);
//    PWM_Source RightLED (
//    .clk(RAW_clk),
//    .speed(speedR),
//    .reset(RAW_reset),
//    .ON(RAW_ON),
//    .PWM(PWM_R)
//    );

    assign LED_SNSA=RAW_SNSA;
    assign LED_SNSB=RAW_SNSB;
    assign LED_Forward1 =RAW_Forward1;
    assign LED_Forward2 =RAW_Forward2;
    assign LED_Backwards1 = RAW_Backwards1;
    assign LED_Backwards2 = RAW_Backwards2;
    assign LED_PWM_L = PWM_L;
    assign LED_PWM_R = PWM_R;
    assign InductiveSNSFlag =(RAW_InductA&&RAW_InductB);
endmodule
