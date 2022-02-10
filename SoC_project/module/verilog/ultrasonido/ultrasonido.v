`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.06.2021 11:40:40
// Design Name: 
// Module Name: ultrasonido
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


module ultrasonido( input clk, // Reloj

                    // Registros
                    input init,
                    output reg [8:0] distance,
                    output reg done,

                    // Conexiones del Dispositivo
                    input echo,
                    output reg trig
                    );

wire clk_1MHz; // Reloj de 1MHz

// Registros auxiliares
reg [14:0] counter = 0;
reg echoStart = 0;

reg [1:0] status = 0; // Registro de Estado
parameter Start = 0, Pulse = 'd1, Echo = 'd2; // Estados

always @ (posedge clk_1MHz) begin
    case(status)
        Start:  begin
                    // Cuando init es 1, se reinician los registros.
                    if(init) begin
                        done = 0;
                        counter = 0;
                        distance = 0;
                        status = Pulse;
                    end
                end
        Pulse:  begin
                    // Trig cambia a 1 por 11 us, luego regresa 0.
                    trig = 1'b1;
                    counter = counter + 1'b1;
                    if(counter == 'd11) begin
                        trig = 0;
                        counter = 0;
                        status = Echo;
                    end
                end
        Echo:   begin
                    // Se espera a que echo sea 1, luego se contabiliza el tiempo hasta que echo sea 0.
                    if(echo) begin
                        echoStart = 1;
                        counter = counter + 1'b1;
                    end
                    if(echo == 0 && echoStart == 1) begin
                        // Si el contador es 0, se vuelve al estado anterior hasta que el resultado sea diferente a 0.
                        if(counter == 0) status = Pulse;
                        else begin
                            // Se divide el contador entre 58 para encontrar la distancia
                            distance = counter/'d58;
                            status = Start;
                            done = 1;
                        end
                    end
                end
    endcase 
end

// Reloj de 1MHz para que el periodo sea de 1 us.
divFreq freq1(clk, 'd50, clk_1MHz);

endmodule
