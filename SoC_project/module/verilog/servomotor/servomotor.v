`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.06.2021 21:11:04
// Design Name: 
// Module Name: servomotor
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


module servomotor(  input clk, // Reloj

                    // Registros
                    input [1:0] posicion,

                    // Conexiones del Dispositivo
                    output reg servo 
                    );

// Registros auxiliares
reg [20:0] contador = 0;

always@(posedge clk)begin
	contador = contador + 1;
	if(contador == 'd1_000_000) begin
	    contador = 0;
	end
	
	case(posicion)
        // Centro
        2'b00:  servo = (contador < 'd150_000) ? 1:0;
        // Izquierda
        2'b01:  servo = (contador < 'd250_000) ? 1:0;
        // Derecha
        2'b10:  servo = (contador < 'd50_000) ? 1:0;
        // Caso por Defecto (Centro)
        default:servo = (contador < 'd150_000) ? 1:0;
    endcase
end

endmodule
