## Ultrasonido 🔊

Para el desarrollo de los drivers correspondientes a este periférico nos guiamos por el trabajo realizado por el Grupo 2 del semestre 2020-II ([Ultrasonido](https://github.com/unal-edigital2/w07_entrega-_final-grupo02/tree/main/Hardware/Modulos/ultrasonido)), en donde para determinar la distancia se utilizan principalmente dos módulos ([contador.v](/Soc_project/module/verilog/ultrasonido/contador.v) y [genpulsos.v](/Soc_project/module/verilog/ultrasonido/genpulsos.v)) junto a otros módulos auxiliares que cumplen la función de divisores de frecuencia para hacer relojes o se encargan de que se cumpla la máquina de estados. El diagrama que describe la conexión entre los drivers de este periférico es el siguiente (para más informacion remitase a [HC-SR04](/datasheets/HC-SR04.pdf)):

![Screenshot](/images/ultra_mem.png)

Y las ubicaciones de los registros en el mapa de memoria [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv) son las siguientes:

```
csr_base,ultrasonido_cntrl,0x82004800,,
```

A continuación se hace la descripción del funcionamiento de los módulos principales correspondientes al ultrasonido.

### Módulo Contador ([contador.v](/Soc_project/module/verilog/ultrasonido/contador.v))
Las funciones de este módulo son activar la generación del pulso que le indica al ultrasonido que debe iniciar a operar, y calcular la distancia entre el ultrasonido y la pared midiendo el ancho de la señal **echo**, la cual es la salida del ultrasonido y proporcional a la distancia. Para que la proporción entre el ancho de la señal y la distancia sea 1 a 1 se utiliza un divisor de frecuencia para generar un reloj cuyos ciclos son equivalentes al tiempo que se demora la señal emitida por el ultrasonido en recorrer 1 cm. El diagrama de bloque que representa el funcionamiento del módulo es el siguiente:

<p align="center">
  <img src="/Imagenes/Contador.PNG" align="center">
</p>


El código utilizado para realizar este proceso es el siguiente:







Podemos observar que la variable **count0** aumenta 1 por cada ciclo del reloj **CLKOUT** mientras que la señal de entrada **echo** se encuentra en 1, de tal forma cuando el pulso **echo** vuelve a tener valor de 0, se almacena en la variable **count** el valor de la distancia entre el ultrasonido y la pared más cercana. De igual forma la variable **calculate** toma valor de 1 cuando se termina de realizar el proceso de medición, actuando como un Done. 

### Módulo Generador de Pulsos ([genpulsos.v](/Soc_project/module/verilog/ultrasonido/genpulsos.v))

La función de este módulo es crear una señal PWM de ancho de 10 microsegundos en alto cuando el módulo [contador.v](/Soc_project/module/verilog/ultrasonido/contador.v) se lo indica. Esta señal corresponde a el **trigg** del ultrasonido, por lo tanto despues de recibir esta señal este empieza a operar y emite las ondas que se reflejan en las paredes del laberinto con el fin de medir la distancia. El diagrama de bloque que representa el funcionamiento del módulo es el siguiente:

<p align="center">
  <img src="/Imagenes/PWM_ultra.PNG" align="center">
</p>


El código utilizado para realizar este proceso es el siguiente:









El reloj **CLKOUT1** tiene período de 10 microsegundos, por lo tanto cuando la señal de entrada **pulse** tiene valor alto, en el primer ciclo del reloj las señales **Doit** y **NoDoit** tendran un valor distinto y por ende la señal de salida **trigg** sera alta durante este período, pero en el siguiente ciclo del reloj las señales seran iguales y la señal **trigg** tendra valor bajo, generando de tal forma un pulso de 10 microsegundos que corresponde a la entrada del ultrasonido.  
