# Firmware 🚨
A continuacion se enunciara las funciones mas importantes para el desarrollo de software de este proyecto, las cuales son utilizadas para realizar pruebas en los perifericos y finalmente realizar una integracion total del funcionamiento de los mismos 

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

![Screenshot](/images/infrar_mem.png)

Por ultimo vemos su espacio de memoria dentro del archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv)

```
csr_base,infrarojo_cntrl,0x82005000,,
```
