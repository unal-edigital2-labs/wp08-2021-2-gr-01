# Entrega Final - Digital II - Grupo 1
## Integrantes 🥵
- Diego Alejandro Sanchez Lopez 😴🕑
- Leonardo Daniel Talledos Rodriguez 😎🌮
- Juan Sebastián Martínez Bohórquez 🙃⚽

## Introducción 📖

Este es el repositorio del proyecto final de la asignatura Electrónica Digital II del semestre 2021-2 (Universidad Nacional de Colombia - Sede Bogotá). La propuesta de proyecto consiste en un Robot Cartográfico conformado por una arquitectura de SoC, donde a partir de un micropocesador y diferentes periféricos se logran realizar operaciones que le permiten al robot recorrer un laberinto con el fin de identificar y mapear en una matriz los muros encontrados y el color correspondiente a estos. 

![Screenshot](/images/pathss.jpeg)

Los periféricos que se utilizaron en este proyecto, fueron una camara (OV7670), 4 sensores infrarrojos, 2 Motorreductores con caja reductora 6V 1:48 controlados a partir de un puente H, un sensor de ultrasonido HC-SR04, un sensor de humedad y temperatura SHT40 y finalmente se utilizó un microprocesador Arduino Uno para realizar diferentes procesos que se explican posteriormente.

El mapa de memoria se encuentra detalladamente en el archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv), las bases correspondientes para cada driver del SoC son las siguientes:

<p align="center">
  <img src="/images/mapa_memoria.png" align="center">
</p>

A continuación haremos una breve explicación del Soc, el firmware y los perfiféricos integrados al Soc junto a sus respectivos links en donde se puede observar su funcionamiento más en detalle.


## [SoC](/SoC_project/) 🤖

En este enlace se describe la arquitectura del robot cartógrafo y el proceso que se llevo a cabo usando el entorno Litex para el ensamble y la integración del microprocesador picoRV32, el bus de datos Wishbone y los diferentes módulos de los periféricos que componen el robot.


El diagrama que describe cómo se encuentra conformado el robot cartógrafo y las diversas conexiones entre el SoC, el microprocesador Arduino y los periféricos usados es el siguiente:


![Screenshot](/images/SoC.png)

## [ Mapa de Memoria ](/SoC_project/Soc_MemoryMap.csv) 🧠

En la presente sección se encuentran los diferentes perífericos que se usaron para la elaboración del robot cartógrafo junto con sus respectivos espacios en memoria que fueron utilizados y como cada uno de estos se creo en hardware y del mismo modo se implemento.

## [ Firmware ](/SoC_project/firmware/) ⚡

En esta seccion se encuentra como se realizo el procesamiento desde software, realizando el codigo para las respectivas pruebas de cada periférico y como se ejecuto para su funcionamiento completo.

## Construcción 🛠

Para la construcción del carrito se utilizaron los siguientes materiales:
- [Kit carro robot](/images/kit_robot.png)
- [2 motorreductores junto con sus llantas](/images/motorreductor.png)
- [1 servomotor](/images/servo.png)
- [1 ultrasonido HC-SR04](/images/ultra.png)
- [5 sensores infrarrojos](/images/infra.png)
- [1 puente H L298N](/images/puente.png)
- [1 mini Protoboard](/images/mini.png)
- [Cámara OV7670](/images/cam.png)
- [Sensor de humedad y temperatura SHT40](/images/sht40.png)



## Módulos 💻
Aquí presentamos una lista de los módulos usados en el robot cartógrafo, cada uno de estos links mostraran el módulo en verilog.
- [Infrarrojos](/SoC_project/module/verilog/infrarojo/)
- [Movimiento](/SoC_project/module/verilog/movimiento/)
- [Servomotor](/SoC_project/module/verilog/servomotor/)
- [Ultrasonido](/SoC_project/module/verilog/ultrasonido/)


## Pruebas de Funcionamiento ⚙

A continuación se muestran los videos correspondientes a las pruebas de funcionamiento realizadas del robot cartógrafo, inicialmente se realizaron algunas pruebas de los periféricos de forma individual, y al final se muestra el funcionamiento completo del robot recorriendo el camino propuesto.
- [Video 1 - Funcionamiento servomotor](https://youtu.be/PJH74lH_T-I)
- [Video 2 - Funcionamiento ultrasonido](https://youtu.be/FX3cMMHn51o)
- [Video 3 - Funcionamiento seguidor de línea](https://youtu.be/vsc-NS2_3Oc)
