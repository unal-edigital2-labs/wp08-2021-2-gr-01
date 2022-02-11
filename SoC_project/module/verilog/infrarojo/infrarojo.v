`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.06.2021 11:40:40
// Design Name: 
// Module Name: infraRed
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


module infrarojo(   
                    // Conexiones del Dispositivo
                    input iL,
                    input iLC,
                    input iC,
                    input iRC,
                    input iR,

                    // Registros
                    output reg oL,
                    output reg oLC,
                    output reg oC,
                    output reg oRC,
                    output reg oR
                    );

always @* begin
    oL = iL;
    oLC = iLC;
    oC = iC;
    oRC = iRC;
    oR = iR;
end

/*
assign oL = iL;
assign oLC = iLC;
assign oC = iC;
assign oRC = iRC;
assign oR = iR;
*/
endmodule