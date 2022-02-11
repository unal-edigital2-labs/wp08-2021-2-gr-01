# Infrarrojo 🚨
El periférico de los sensores seguidores de línea está conformado por 5 sensores infrarrojos tal como se observa a continuación:

<p align="center">
  <img src="/Imagenes/IR.jpeg" align="center">
</p>

Los sensores infrarrojos poseen 3 pines(GND, Vcc, out), de esta forma, solo tenemos 5 conexiones del periférico con el driver [infrarojo](/SoC_project/module/verilog/infrarojo/infrarojo.v).

A continuación observamos el módulo en verilog del infrarrojo, el desarrollo de este es.....

```verilog
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

endmodule
```
A continuación podemos observar el diagrama de bloques que describe la conexión del periférico de los sensores infrarrojos en nuestro proyecto, esto es posible gracias al módulo ([infrarrojo.py](/SoC_project/module/infrarojo.py)) que obtiene un espacio de memoria gracias al modulo general de ([buildSoCproject.py](/SoC_project/buildSoCproject.py))   

![Screenshot](/images/infra_mem.png)

Por ultimo vemos su espacio de memoria dentro del archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv)

```
csr_base,infrarojo_cntrl,0x82005000,,
```
