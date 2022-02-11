## Servomotor 🔧

El driver de este periférico corresponde a un simple módulo PWM, ya que el desplazamiento angular del servomotor se define por el ciclo útil de una señal PWM con período de 20 milisegundos.  El diagrama que describe la conexión entre el driver y el periférico es el siguiente (para más informacion remitase a [Futaba S3003](/datasheets/s003.pdf)):

![Screenshot](/Imagenes/servos.png)

La ubicación del registro en el mapa de memoria [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv) es:

```
csr_base,servomotor_cntrl,0x82004000,,
```

El diagrama de bloques que describe el funcionamiento del módulo es el siguiente: 

<p align="center">
  <img src="/images/servo_mem.png" align="center">
</p>


El código utilizado para realizar este módulo es el siguiente:

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
 
El funcionamiento del código se basa en que ..... 
