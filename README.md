# Entrega Final - Digital II - Grupo 1
## Integrantes 🥵
- Diego Alejandro Sanchez Lopez 🕒
- Leonardo Daniel Talledos Rodriguez 🌮
- Juan Sebastián Martínez Bohórquez ⚽

## Introducción 📖

Este es el repositorio del proyecto final de la asignatura Electrónica Digital II del semestre 2021-2 (Universidad Nacional de Colombia - Sede Bogotá). La propuesta de proyecto consiste en un Robot Cartográfico conformado por una arquitectura de SoC, donde a partir de un micropocesador y diferentes periféricos se logran realizar operaciones que le permiten al robot recorrer un laberinto con el fin de identificar y mapear en una matriz los muros encontrados y el color correspondiente a estos. 

![Screenshot](/Imagenes/robot.jpeg)

Los periféricos que se utilizaron en este proyecto, fueron una camara (OV7670), 4 sensores infrarrojos, 2 Motorreductores con caja reductora 6V 1:48 controlados a partir de un puente H, un sensor de ultrasonido HC-SR04, un sensor de humedad y temperatura SHT40 y finalmente se utilizó un microprocesador Arduino Uno para realizar diferentes procesos que se explican posteriormente.

El diagrama que describe cómo se encuentra conformado el robot cartógrafo y las diversas conexiones entre el SoC, el microprocesador Arduino y los periféricos usados es el siguiente:

![Screenshot](/Imagenes/Diagrama.png)

El mapa de memoria se encuentra detalladamente en el archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv), las bases correspondientes para cada driver del SoC son las siguientes:

<p align="center">
  <img src="/Imagenes/mem_bases.PNG" align="center">
</p>

A continuación haremos una breve explicación del Soc, el firmware y los perfiféricos integrados al Soc junto a sus respectivos links en donde se puede observar su funcionamiento más en detalle.

## [SoC](/SoC_project/)

En este enlace se describe la arquitectura del robot cartógrafo y el proceso que se llevo a cabo usando el entorno Litex para el ensamble y la integración del microprocesador picoRV32, el bus de datos Wishbone y los diferentes módulos de los periféricos que componen el robot. Para mas informacion remitase a [Soc](/Soc_project/). 

## [Firmware](/SoC_project/firmware/) 
Dentro del enlace de firmware se encuentra la información del código usado para el desarrollo del funcionamiento del robot cartógrafo, de igual forma se puede observar la explicación de las funciones que se encuentran dentro del archivo [main.c](/Soc_project/firmware/main.c). Para mas informacion remitase a [firmware](/Soc_project/firmware/). 

## [Módulos](/SoC_project/module/)
Aquí presentamos una lista de los periféricos usados en el robot cartógrafo, cada uno de estos links mostraran el módulo en verilog y a su vez se hace una explicación detallada del código utilizado para el funcionamiento del módulo de cada periférico.
- [Cámara](/SoC_project/module/verilog/camara/)
- [Infrarrojos](/SoC_project/module/verilog/infrarojo/)
- [Movimiento](/SoC_project/module/verilog/movimiento/)
- [Servomotor](/SoC_project/module/verilog/servomotor/)
- [SHT40](/SoC_project/module/verilog/sht40/)
- [Ultrasonido](/SoC_project/module/verilog/ultrasonido/)

## Mantener código cargado FPGA

### Alimentación:
El proyecto en general, a excepción de los motores, se alimenta con una powerbank de dos puertos que provee de energía tanto a la FPGA como a el Arduino Mega2560.
<p align="center">
  <img src="/Imagenes/powerbank.jpeg" align="center" width="400px">
</p>

### Mantener Hardware y Firmware FPGA:
Es claro que al momento de realizar la sintetización del hardware, la compilación del firmware y cargar todo a la FPGA, todo funciona correctamente mientras se mantenga conectada al computador. Sin embargo al momento de desconectar el micro-usb(J6) por el cual se está alimentado y cargando los archivos a la FPGA, se pierden todos los cambios ejecutados sobre esta. Por este motivo se decidio mantener la FPGA encendida en todo momento para que no se pierdan el archivo de hardware y las diferentes compilaciones de firmware que se ejecuten en el proceso de testeo.
Cabe aclarar que se esta trabajando con una **FPGA - Nexys 4DDR**, y que esta tarjeta nos da la posibilidad de cambiar su puerto de alimentacion, por lo que el procedimiento es simple y consiste en cambiar la alimentacion de la FPGA del puerto micro-usb(J6) al Jack(J13).

<p align="center">
  <img src="/Imagenes/alime.png" align="center">
</p>

Para hacer dicho cambio, se cambia la ubicacion de el jumper JP3 dependiendo de la alimentacion que se desee utilizar. (**NOTA : La tension en el Jack(J13) debe ser 5V exclusivamente** para mas informacion remitase a [Nexys4DDR](/datasheets/Nexys4-DDR_rm.pdf)).

## Pruebas de Funcionamiento :clapper:

En los siguientes enlaces se encuentran los videos correspondientes a las pruebas de funcionamiento realizadas al robot cartógrafo, en ellos se puede observar al robot recorriendo el laberinto de forma autónoma a medida que reconoce los colores de las paredes. De igual forma, se observa simultaneamente la impresión del mapeo realizado por el robot que se envía a un celular por medio de bluetooth.
- [Video 1](https://www.youtube.com/watch?v=-sIw7MB7exA)
- [Video 2](https://www.youtube.com/watch?v=XjEla83Jrmw)


### Problemas Presentados :shipit: :warning:

Durante la realización del proyecto se presentaron diversos problemas, los más significativos fueron los siguientes:
- **Detección de colores:** Después de realizar distintas pruebas al módulo de la cámara encargado de analizar las imágenes capturadas, notamos que se presentaban problemas al momento de detectar los colores ya que en algunas ocasiones no se detectaba el color correcto, esto se puede evidenciar en los videos de prueba de funcionamiento del robot cartógrafo en donde el robot detecta el color erroneo en algunas paredes del laberinto. Este problema se debe a que, por las limitaciones de la cámara utilizada, cuando la iluminación del ambiente no es ideal la captura de datos es erronea y la activación de los pixeles RGB no se da de forma correcta. 
- **Módulo Bluetooth:** Se nos presento otro inconveniente al tratar de implementar el módulo bluetooth HC-05 con un periférico UART generado en la FPGA, a pesar de que se tuvo en cuenta los baudios a los que trabajaba el dispositivo (9600), no pudimos lograr que mediante de la FPGA pudieramos enviar datos por bluetooth. Debido a ello, decidimos realizar la implementación de la comunicación bluetooth con uno de los seriales que presta el Arduino Mega 2560 (tanto para recepción como para envío de información).
- **Motorreductores:** En tanto a los motorreductores, al hacer pruebas de funcionamiento del robot cartógrafo, nos percatamos que perdían potencia a medida que ejecutabamos prueba tras prueba, esto resultaba en que los tiempos de giro variaran cada vez, y que el carro no quedase orientado correctamente en la dirección que está supuesto a tomar. Para ese entonces teniamos energizados los motores con una bateria de 9V externa que alimentaba el puente H con el cual funcionaban los motores. Por lo tanto optamos por alimentar el puente H con 12V suministrados por 8 pilas recargables AA en serie, de está manera podemos asegurar que cada vez que realizemos pruebas los motores del motor funcionen a la misma potencia.
