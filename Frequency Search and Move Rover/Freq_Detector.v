
module Freq_Detector(
    input clk,
    input MicA,
    output[3:0] FreqState
    );
reg [15:0] Fcount1; 
reg [15:0] ActualFreq;
reg [3:0] FreqState_temp;
reg [1:0]Signal;
initial begin
    Fcount1    = 0;
    ActualFreq        = 0;
    FreqState_temp      = 0;
end   
 
always @(posedge clk)
begin
 
        Signal<={Signal[0], MicA};
        if (Signal[1]&&~Signal[0])
        begin
            ActualFreq   <= Fcount1;
            Fcount1 <= 0;
        end
        else
        begin
            Fcount1 <= Fcount1 + 1;
        end 
        
if( ActualFreq >= 6897 && ActualFreq <= 7406)
 begin
    FreqState_temp <= 14;
  end
else if(ActualFreq >=7407  && ActualFreq <= 8000)
  begin
    FreqState_temp <= 13;
  end		  
else if(ActualFreq >= 8001 && ActualFreq <= 8694)
  begin
    FreqState_temp <= 12;
  end
else if(ActualFreq >= 8694 && ActualFreq <= 9521)
 begin
    FreqState_temp <= 11;
 end
else if( ActualFreq >= 9522 && ActualFreq <= 10527)
 begin
    FreqState_temp <= 10;
 end 
else if( ActualFreq >= 10528 && ActualFreq <= 11765)
 begin
    FreqState_temp <= 9;
 end
else if( ActualFreq >= 11766 && ActualFreq <= 13333)
  begin
     FreqState_temp <= 8;
  end
else if( ActualFreq >= 13334 && ActualFreq <= 15385)
  begin
     FreqState_temp <= 7;
  end
end   
    
assign FreqState = FreqState_temp; 
endmodule
