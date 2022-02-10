`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.06.2021 18:48:27
// Design Name: 
// Module Name: divFreq
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


module divFreq(	input clk, // Reloj de Entrada
				input [28:0] max_cont, // Valor maximo para contador dado por [max_cont = 100Mhz/(2*Frecuencia Nueva)]
				output reg newCLK // Reloj de Salida 
				);

initial begin
    newCLK = 0;
end

// Registros auxiliares
reg [28:0] contador = 0;

always @(posedge clk) begin
	//Cuenta hasta el valor de max_cont
	contador = contador + 1'b1;
	if(contador == max_cont) begin
		//Se reinicia el contador y se niega el valor de newCLK
		contador = 0;
		newCLK = !newCLK;
	end
end

endmodule
