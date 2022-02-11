# Infrarrojo 〰
El periférico de los sensores seguidores de línea está conformado por 5 sensores infrarrojos tal como se observa a continuación:

<p align="center">
  <img src="/Imagenes/IR.jpeg" align="center">
</p>

Los sensores infrarrojos poseen 3 pines(GND, Vcc, out), """por lo cual se tienen 5 conexiones con el driver además de otros dos pines que cumplen la función de conexión a tierra GND y de alimentación con 5V que se obtienen del arduino""".

A continuación observamos el módulo en verilog del infrarrojo, el desarrollo de este es.....

```verilog
module infrarojo(   
          // Conexiones del Dispositivo
          input ising,

          // Registros
          output osing
          );

assign osing = ising;

endmodule
```
A continuación podemos observar el diagrama de bloques que describe la conexión del periférico de los sensores infrarrojos en nuestro proyecto, esto es posible gracias al módulo ([infrarrojo.py](/SoC_project/module/infrarojo.py)) que obtiene un espacio de memoria gracias al modulo general de ([buildSoCproject.py](/SoC_project/buildSoCproject.py))   

![Screenshot](/images/infra_mem)

Por ultimo vemos su espacio de memoria dentro del archivo **Soc_MemoryMap.csv**.

<p align="center">
  <img src="/Imagenes/mem_infra.PNG" align="center">
</p>
