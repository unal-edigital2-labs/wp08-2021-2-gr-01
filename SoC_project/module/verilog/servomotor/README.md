## Servomotor 馃敡

El driver de este perif茅rico corresponde a un simple m贸dulo PWM, ya que el desplazamiento angular del servomotor se define por el ciclo 煤til de una se帽al PWM con per铆odo de 20 milisegundos.  El diagrama que describe la conexi贸n entre el driver y el perif茅rico es el siguiente (para m谩s informacion remitase a [Futaba S3003](/datasheets/s003.pdf)):

![Screenshot](/Imagenes/servos.png)

La ubicaci贸n del registro en el mapa de memoria [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv) es:

```
csr_base,servomotor_cntrl,0x82004000,,
```

El diagrama de bloques que describe el funcionamiento del m贸dulo es el siguiente: 

<p align="center">
  <img src="/images/servo_mem.png" align="center">
</p>


El c贸digo utilizado para realizar este m贸dulo es el siguiente:

```verilog
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
 ```
 
El funcionamiento del c贸digo se basa en que ..... 
