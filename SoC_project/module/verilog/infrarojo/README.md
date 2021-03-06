# Infrarrojo 馃毃
El perif茅rico de los sensores seguidores de l铆nea est谩 conformado por 5 sensores infrarrojos tal como se observa a continuaci贸n:

<p align="center">
  <img src="/Imagenes/IR.jpeg" align="center">
</p>

Los sensores infrarrojos poseen 3 pines(GND, Vcc, out), """por lo cual se tienen 5 conexiones con el driver adem谩s de otros dos pines que cumplen la funci贸n de conexi贸n a tierra GND y de alimentaci贸n con 5V que se obtienen del arduino""".

A continuaci贸n observamos el m贸dulo en verilog del infrarrojo, el desarrollo de este es.....

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

/*
assign oL = iL;
assign oLC = iLC;
assign oC = iC;
assign oRC = iRC;
assign oR = iR;
*/
endmodule
```
A continuaci贸n podemos observar el diagrama de bloques que describe la conexi贸n del perif茅rico de los sensores infrarrojos en nuestro proyecto, esto es posible gracias al m贸dulo ([infrarrojo.py](/SoC_project/module/infrarojo.py)) que obtiene un espacio de memoria gracias al modulo general de ([buildSoCproject.py](/SoC_project/buildSoCproject.py))   

![Screenshot](/images/infrar_mem.png)

Por ultimo vemos su espacio de memoria dentro del archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv)

```
csr_base,infrarojo_cntrl,0x82005000,,
```
