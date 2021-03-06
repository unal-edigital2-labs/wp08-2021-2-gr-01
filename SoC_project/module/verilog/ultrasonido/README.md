## Ultrasonido 馃攰

Para el desarrollo de los drivers correspondientes a este perif茅rico nos guiamos por el trabajo realizado por el Grupo 2 del semestre 2020-II ([Ultrasonido](https://github.com/unal-edigital2/w07_entrega-_final-grupo02/tree/main/Hardware/Modulos/ultrasonido)), en donde para determinar la distancia se utilizan principalmente dos m贸dulos ([contador.v](/Soc_project/module/verilog/ultrasonido/contador.v) y [genpulsos.v](/Soc_project/module/verilog/ultrasonido/genpulsos.v)) junto a otros m贸dulos auxiliares que cumplen la funci贸n de divisores de frecuencia para hacer relojes o se encargan de que se cumpla la m谩quina de estados. El diagrama que describe la conexi贸n entre los drivers de este perif茅rico es el siguiente (para m谩s informacion remitase a [HC-SR04](/datasheets/HC-SR04.pdf)):

![Screenshot](/Imagenes/ultra.png)

Y las ubicaciones de los registros en el mapa de memoria (**Soc_MemoryMap.csv**) son las siguientes:

<p align="center">
  <img src="/Imagenes/mem_ultra.PNG" align="center">
</p>


A continuaci贸n se hace la descripci贸n del funcionamiento de los m贸dulos principales correspondientes al ultrasonido.

### M贸dulo Contador ([contador.v](/Soc_project/module/verilog/ultrasonido/contador.v))
Las funciones de este m贸dulo son activar la generaci贸n del pulso que le indica al ultrasonido que debe iniciar a operar, y calcular la distancia entre el ultrasonido y la pared midiendo el ancho de la se帽al **echo**, la cual es la salida del ultrasonido y proporcional a la distancia. Para que la proporci贸n entre el ancho de la se帽al y la distancia sea 1 a 1 se utiliza un divisor de frecuencia para generar un reloj cuyos ciclos son equivalentes al tiempo que se demora la se帽al emitida por el ultrasonido en recorrer 1 cm. El diagrama de bloque que representa el funcionamiento del m贸dulo es el siguiente:

<p align="center">
  <img src="/Imagenes/Contador.PNG" align="center">
</p>


El c贸digo utilizado para realizar este proceso es el siguiente:







Podemos observar que la variable **count0** aumenta 1 por cada ciclo del reloj **CLKOUT** mientras que la se帽al de entrada **echo** se encuentra en 1, de tal forma cuando el pulso **echo** vuelve a tener valor de 0, se almacena en la variable **count** el valor de la distancia entre el ultrasonido y la pared m谩s cercana. De igual forma la variable **calculate** toma valor de 1 cuando se termina de realizar el proceso de medici贸n, actuando como un Done. 

### M贸dulo Generador de Pulsos ([genpulsos.v](/Soc_project/module/verilog/ultrasonido/genpulsos.v))

La funci贸n de este m贸dulo es crear una se帽al PWM de ancho de 10 microsegundos en alto cuando el m贸dulo [contador.v](/Soc_project/module/verilog/ultrasonido/contador.v) se lo indica. Esta se帽al corresponde a el **trigg** del ultrasonido, por lo tanto despues de recibir esta se帽al este empieza a operar y emite las ondas que se reflejan en las paredes del laberinto con el fin de medir la distancia. El diagrama de bloque que representa el funcionamiento del m贸dulo es el siguiente:

<p align="center">
  <img src="/Imagenes/PWM_ultra.PNG" align="center">
</p>


El c贸digo utilizado para realizar este proceso es el siguiente:









El reloj **CLKOUT1** tiene per铆odo de 10 microsegundos, por lo tanto cuando la se帽al de entrada **pulse** tiene valor alto, en el primer ciclo del reloj las se帽ales **Doit** y **NoDoit** tendran un valor distinto y por ende la se帽al de salida **trigg** sera alta durante este per铆odo, pero en el siguiente ciclo del reloj las se帽ales seran iguales y la se帽al **trigg** tendra valor bajo, generando de tal forma un pulso de 10 microsegundos que corresponde a la entrada del ultrasonido.  
