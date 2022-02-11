## Servomotor ([pwm.v](/Soc_project/module/verilog/ultrasonido/pwm.v))

El driver de este periférico corresponde a un simple módulo PWM, ya que el desplazamiento angular del servomotor se define por el ciclo útil de una señal PWM con período de 20 milisegundos.  El diagrama que describe la conexión entre el driver y el periférico es el siguiente (para más informacion remitase a [Futaba S3003](/datasheets/s003.pdf)):

![Screenshot](/Imagenes/servos.png)

Y las ubicaciones de los registros en el mapa de memoria (**Soc_MemoryMap.csv**) son las siguientes:

<p align="center">
  <img src="/Imagenes/mem_servo.PNG" align="center">
</p>


El diagrama de bloques que describe el funcionamiento del módulo es el siguiente: 

<p align="center">
  <img src="/Imagenes/pwm.PNG" align="center">
</p>


El código utilizado para realizar este módulo es el siguiente:

```verilog
      reg[27:0] counter=28'd0;
      reg[15:0] limite;
      reg[15:0] activo;

      always @(posedge clk) begin

      counter <= counter + 28'd1;

           if(counter>=(period-1))
              counter <= 28'd0;

           if(counter <= dutty)
              pwm <= 1;
              else
              pwm <=0;

      end
 ```
 
El funcionamiento del código se basa en que se define un contador que aumenta con cada ciclo del reloj, y cuando el valor del contador es menor que la señal de entrada **dutty** correspondiente al ciclo útil, la señal de salida **pwm** tiene valor alto mientras que si el contador es mayor al ciclo útil la señal de salida se torna a valor bajo, y en el momento que el contador tiene el mismo valor que la señal de entrada **period**, este se reinicia repitiendo el proceso descrito anteriormente. 
