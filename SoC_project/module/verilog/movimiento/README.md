# Movimiento 🏎

Se utilizaron dos motorreductores controlados mediante un puente H (L298N) para el movimiento del robot cartógrafo, despues de varias pruebas se decidio alimentar a los motores con 12V para que tuvieran un desempeño óptimo.
<p align="center">
  <img src="/Imagenes/DC.jpeg" align="center" width="400px" >
</p>

Para la implementación del puente H, se establecieron 5 posibles estados, los cuales permiten que el robot avance, gire o se detenga, en la siguiente tabla muestran las acciones de movimiento que se realizan de acuerdo al valor de las entradas del puente H.

 | Acción | left[0] | left[1] | right[0] | right[1] |
| ------------- | ------------- | ------------- |------------- |------------- |
| Parar | 0 | 0 | 0 | 0 |
| Avanzar | 1 | 0 | 1 | 0 |
| Retroceder | 0 | 1 | 0 | 1 |
| Izquierda | 0 | 1 | 1 | 0 |
| Derecha | 1 | 0 | 0 | 1 | 



Teniendo en cuenta la anterior tabla se desarrollo el módulo [movimiento.v](/SoC_project/module/verilog/movimiento/) que cumple la función de driver para los motores. El diagrama que describe las conexiones de este driver con el periférico es el siguiente:

![Screenshot](/images/mov_mem.png)

Y la ubicación del registro en el mapa de memoria es:
```
csr_base,movimiento_cntrl,0x82003800,,
```



El código utilizado para la realización del módulo es el siguiente:

```
module movimiento(  input clk, // Reloj

                    // Registros
                    input [2:0] estado,
                    
                    // Conexiones del Dispositivo 
                    output reg [1:0] right,
                    output reg [1:0] left
                    );
    
always@(posedge clk)begin
	case(estado)
        // Parar
        3'b000: begin
                    right[0] = 0;
                    right[1] = 0;
                    left[0]  = 0;
                    left[1]  = 0;
                end
        // Avanzar
        3'b001: begin
                    right[0] = 1;
                    right[1] = 0;
                    left[0]  = 1;
                    left[1]  = 0;
                end
        // Retroceder
   	    3'b010: begin
                    right[0] = 0;
                    right[1] = 1;
                    left[0]  = 0;
                    left[1]  = 1;
                end
        // Izquierda
        3'b011: begin
                    right[0] = 1;
                    right[1] = 0;
                    left[0]  = 0;
                    left[1]  = 1;
                end
        // Derecha
        3'b100: begin
                    right[0] = 0;
                    right[1] = 1;
                    left[0]  = 1;
                    left[1]  = 0;
                end
        // Caso por Defecto (Parar)
        default:begin
                    right[0] = 0;
                    right[1] = 0;
                    left[0]  = 0;
                    left[1]  = 0;
                end
	endcase
end

endmodule

```
      
El funcionamiento del módulo se basa en una máquina de estados, en la que se define el movimiento del carro de acuerdo al valor de la señal de entrada **estado**, en la que se establecen los valores de salida al igual que se muestra previamente en la tabla.
