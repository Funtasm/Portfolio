`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/24/2017 08:46:13 PM
// Design Name: 
// Module Name: Motor_Drive
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


module Motor_Drive(
    input clk,reset,resetL,resetR,
    input ON_CURRENT,InductiveSNS,Direction,Rotate,Move,
    input [3:0]FreqState,
    output Forward1,Backwards1, Forward2,Backwards2,RED,BLUE,GREEN,
    wire [1:0]speedL,
    wire [1:0]speedR

    
    );
     reg temp_Forward1, temp_Backwards1, temp_Forward2, temp_Backwards2;
     reg tempRED, tempGREEN, tempBLUE;
     reg [24:0]ToggleCounter;
     reg ResetFlag;
     reg [32:0]ResetTimer1;
     reg [32:0]ResetTimer2;
     reg State;
     reg InductiveSNSFlag;
     reg [1:0]Temp_speedL;
     reg [1:0]Temp_speedR;
     reg ResetFlag2;
     reg ResetFlag3;
     reg Reset1Timer1;
     reg Reset1Timer2;
     reg Reset2Timer1;
     reg Reset2Timer2;
    initial begin
      temp_Forward1 <=0;
      temp_Forward2 <=0;
      temp_Backwards1 <=0;
      temp_Backwards2 <=0;
      tempRED <=0;
      tempGREEN <=0;
      tempBLUE <=0;
      ToggleCounter<=0;
      ResetFlag<=0;
      ResetTimer1<=0;
      ResetTimer2<=0;
      ResetFlag2<=0;
      ResetFlag3<=0;
      State<=0;
      InductiveSNSFlag<=1;
      Temp_speedL<=2;
      Temp_speedR<=2;
      Reset1Timer1<=0;
      Reset1Timer2<=0;
      Reset2Timer1<=0;
      Reset2Timer2<=0;
      end
      //left switch is direction, right switch is rotation toggle.
      always@(posedge clk) begin
       ToggleCounter<=ToggleCounter+1;
       if (reset) begin
       ResetFlag<=1;
       ResetTimer1<=175000000;
       ResetTimer2<=200000000;
       end
       if (resetL) begin
       ResetFlag2<=1;
       Reset1Timer1<=175000000;
       Reset1Timer2<=300000000;
       end
       if (resetR) begin
       ResetFlag3<=1;
       Reset2Timer1<=175000000;
       Reset2Timer2<=300000000;
       end
  if (~InductiveSNS)begin
  InductiveSNSFlag<=0;
  end    
          if(ON_CURRENT)
          begin
           if(InductiveSNSFlag && ~ResetFlag && ~ResetFlag2 && ~ResetFlag3)
           begin
           tempBLUE<=0;
           tempGREEN<=0;
           tempRED<=0;
            if(Move)
            begin
                 if (Direction)
                 begin
                    if(Rotate)
                     begin
                     
                     //Stop 'n Search Settings         
//                      temp_Forward1 <=0;
//                      temp_Forward2 <=1;
//                      temp_Backwards1 <=1;
//                      temp_Backwards2 <=0;
//                      Temp_speedL<=2;
//                      Temp_speedR<=2;                 
                     //TokyoDrift Settings   
                      temp_Forward1 <=0;
                      temp_Forward2<=1;
                      temp_Backwards1<=0;
                      temp_Backwards2<=0;
                      Temp_speedL<=0;
                      Temp_speedR<=2;
                     end
                    else
                      begin
                      
//                      //Stop 'n Search Settings
//                         temp_Forward1 <=1;
//                         temp_Forward2 <=1;
//                         temp_Backwards1 <=0;
//                         temp_Backwards2 <=0;
//                         Temp_speedL<=2;
//                         Temp_speedR<=2; 
//                      //Tokyo Drift Settings
                           temp_Forward1 <=1;
                           temp_Forward2 <=1;
                           temp_Backwards1<=0;
                           temp_Backwards2<=0;
                           Temp_speedL<=3;
                           Temp_speedR<=3;
                      end
                 end
                 else
                 begin
                    if(Rotate)
                     begin
//                 //Stop 'n Search Settings                                  
//                     temp_Forward1 <=0;
//                     temp_Forward2 <=1;
//                     temp_Backwards1 <=1;
//                     temp_Backwards2 <=0; 
//                     Temp_speedL<=2;
//                     Temp_speedR<=2;
//                 //Tokyo Drift Settings
                     temp_Forward1 <=1;
                     temp_Forward2<=0;
                     temp_Backwards1<=0;
                     temp_Backwards2<=0;
                     Temp_speedL<=2;
                     Temp_speedR<=0;
                         
                     end
                    else
                    begin
                    //Going backwards is for squares :)
//                    temp_Forward1 <=0;
//                    temp_Forward2 <=0;
//                    temp_Backwards1 <=1;
//                    temp_Backwards2 <=1;
                    end 
                 end
            end
            else//~Move
             begin
              temp_Forward1 <=0;
              temp_Forward2 <=0;
              temp_Backwards1 <=0;
              temp_Backwards2 <=0;
            end
           end
           else if (~InductiveSNSFlag && ((~ResetFlag && ~ResetFlag2) && ~ResetFlag3)) //~InductiveSNS
           begin
           
            temp_Forward1<=0;
            temp_Forward2<=0;
            temp_Backwards1<=0;
            temp_Backwards2<=0;
              if ((FreqState==9) &&(ToggleCounter==0))
              begin                              
              tempBLUE<=~tempBLUE;
              tempGREEN<=0;
              tempRED<=0;
              end
              else if ((FreqState==10) &&(ToggleCounter==0))
              begin
              tempBLUE<=0;
              tempGREEN<=0;
              tempRED<=~tempRED;
              end
              else if ((FreqState==11) &&(ToggleCounter==0))
              begin
              tempBLUE<=0;
              tempGREEN<=~tempGREEN;
              tempRED<=0;
              end
              else if (FreqState >11 && FreqState<9)
              begin
              tempBLUE<=0;
              tempGREEN<=0;
              tempRED<=0;
              end   
           end
          else if (ResetFlag) begin
          tempBLUE<=0;
          tempGREEN<=0;
          tempRED<=0;
            if(State==0)begin
            temp_Forward1 <=3;
            temp_Forward2 <=0;
            temp_Backwards1 <=0;
            temp_Backwards2 <=0;
            Temp_speedL<=3;
            Temp_speedR<=0;
            ResetTimer1<=ResetTimer1-1;
             if (ResetTimer1==0) begin
             State<=1;
             end
            end
             if(State==1)begin
             temp_Forward1 <=1;
             temp_Forward2 <=1;
             temp_Backwards1 <=0;
             temp_Backwards2 <=0;
             Temp_speedL<=2;
             Temp_speedR<=2;
             ResetTimer2<=ResetTimer2-1;
              if (ResetTimer2==0)
              begin
              State<=0;
              ResetFlag<=0;
              InductiveSNSFlag<=1;
              end
             end    
           end
         else if (ResetFlag2) begin
                    tempBLUE<=0;
                    tempGREEN<=0;
                    tempRED<=0;
                      if(State==0)begin
                      temp_Forward1 <=0;
                      temp_Forward2 <=1;
                      temp_Backwards1 <=1;
                      temp_Backwards2 <=0;
                      Temp_speedL<=3;
                      Temp_speedR<=3;
                      Reset1Timer1<=Reset1Timer1-1;
                       if (Reset1Timer1==0) begin
                       State<=1;
                       end
                      end
                       if(State==1)begin
                       temp_Forward1 <=1;
                       temp_Forward2 <=1;
                       temp_Backwards1 <=0;
                       temp_Backwards2 <=0;
                       Temp_speedL<=2;
                       Temp_speedR<=2;
                       Reset1Timer2<=Reset1Timer2-1;
                        if (Reset1Timer2==0)
                        begin
                        State<=0;
                        ResetFlag2<=0;
                        InductiveSNSFlag<=1;
                        end
                       end    
                     end
           else if(ResetFlag3)begin
                          tempBLUE<=0;
                          tempGREEN<=0;
                          tempRED<=0;
                            if(State==0)begin
                            temp_Forward1 <=1;
                            temp_Forward2 <=0;
                            temp_Backwards1 <=0;
                            temp_Backwards2 <=1;
                            Temp_speedL<=3;
                            Temp_speedR<=3;
                            Reset2Timer1<=Reset2Timer1-1;
                             if (Reset2Timer1==0) begin
                             State<=1;
                             end
                            end
                             if(State==1)begin
                             temp_Forward1 <=1;
                             temp_Forward2 <=1;
                             temp_Backwards1 <=0;
                             temp_Backwards2 <=0;
                             Temp_speedL<=2;
                             Temp_speedR<=2;
                             Reset2Timer2<=Reset2Timer2-1;
                              if (Reset2Timer2==0)
                              begin
                              State<=0;
                              ResetFlag3<=0;
                              InductiveSNSFlag<=1;
                              end
                             end    
                           end     
          end
          else//Not ON_CURRENT
          begin  
                 temp_Forward1 <=0;
                 temp_Forward2 <=0;
                 temp_Backwards1 <=0;
                 temp_Backwards2 <=0;
          end 
end
             
      //  end    
             assign Forward1 = temp_Forward1;
             assign Forward2 = temp_Forward2;
             assign Backwards1 = temp_Backwards1;
             assign Backwards2 = temp_Backwards2;
             assign RED = tempRED;
             assign BLUE = tempBLUE;
             assign GREEN = tempGREEN;
             assign speedL = Temp_speedL;
             assign speedR = Temp_speedR;
       
endmodule
