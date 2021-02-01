`timescale 1ns / 1ps

//------------------------------------
//Remember to change Mdrive settings!
//------------------------------------ 

module Localization(
input clk,
input MicA,
input MicB,
output Direction, Rotate, Move
);
reg TempDirection;
reg TempRotate;
reg TempMove;
reg MicAEdge;
reg MicBEdge;
reg [1:0]SignalA;//for getting posedge mica
reg [1:0]SignalB;//for getting posedge micb
reg [15:0]Timer;
reg [1:0]WhichMicFirst;//MicA ==1, MicB==2;
reg TimerFlag;
reg [26:0]MovementTime;
reg [15:0]Timer1;
reg [1:0]State;
reg [24:0]StateTimer;
reg [26:0]MovementTime1;
reg SearchFlag;
reg [3:0]SearchCycle;


initial begin
TempDirection<=0;
TempRotate<=0;
TempMove<=0;
MicAEdge<=0;
MicBEdge<=0;
Timer<=0;
Timer1<=0;
SignalA<=0;
SignalB<=0;
TimerFlag<=0;
MovementTime<=0;
WhichMicFirst<=0;
State<=0;
StateTimer<=0;
MovementTime<=0;
SearchFlag<=1;
SearchCycle<=0;
end
//Edge detection
always@(posedge clk) begin
SignalA<={SignalA[0], MicA};
SignalB<={SignalB[0], MicB};
if (~SignalA[1] && SignalA[0])begin
    MicAEdge<=1;
end
else begin
    MicAEdge<=0;
end
if (~SignalB[1] &&SignalB[0])begin
    MicBEdge<=1;
end
else begin
    MicBEdge<=0;
end
//~~~~~~~~~~~~~~~~~~~~~~~~~~`
if (TimerFlag) begin
Timer<=Timer+1;
end
else begin
Timer<=0;
end
if (Timer>13000) begin
Timer<=0;
WhichMicFirst<=0;
end
//~~~~~~~~~~~~~~~~~~~~~~~~~
if (MicAEdge && ~MicBEdge && ~MicB) begin
TimerFlag<=1;
WhichMicFirst<=1; //A is first
end
else if (MicAEdge && ~MicBEdge && (WhichMicFirst != 1)) begin
TimerFlag<=0;
WhichMicFirst<=2;
MovementTime<=Timer*9000;
end
else if (MicAEdge && ~MicBEdge && (WhichMicFirst ==1)) begin
TimerFlag<=0;
WhichMicFirst<=0;
end
if (MicBEdge && ~MicAEdge && ~MicA) begin
TimerFlag<=1;
WhichMicFirst<=2;//B is first
end
else if (MicBEdge && ~MicAEdge && (WhichMicFirst != 2)) begin
TimerFlag<=0;
WhichMicFirst<=1;
MovementTime<=Timer*9000;
end
else if (MicBEdge && ~MicAEdge && (WhichMicFirst ==2)) begin
TimerFlag<=0;
WhichMicFirst<=0;
end
if (MicAEdge && MicBEdge) begin
MovementTime<=300000;
WhichMicFirst<=3;
end
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if(WhichMicFirst==1 && (MovementTime>300000))begin
MovementTime<=MovementTime-1;
TempDirection<=1;
TempRotate<=1;
TempMove<=1;
end
if(WhichMicFirst==2 && (MovementTime>300000))begin //was 300000 before
MovementTime<=MovementTime-1;
TempDirection<=0;
TempRotate<=1;
TempMove<=1;
end
if(WhichMicFirst!=0 &&(MovementTime<300001) && (MovementTime>1)) begin //was 300001
MovementTime<=MovementTime-1;
TempDirection<=1;
TempRotate<=0;
TempMove<=1;
end
if(MovementTime<2) begin // changed WhichMicFirst==0 to MovementTime <2
TempMove<=0;
end
end
assign Direction = TempDirection;
assign Rotate = TempRotate;
assign Move = TempMove;
endmodule
