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
                    output oL,
                    output oLC;
                    output oC;
                    output oRC;
                    output oR;
                    );

assign oL = iL;
assign oLC = iLC;
assign oC = iC;
assign oRC = oRC;
assign oR = iR;

endmodule