# Movimiento 🏎

Se utilizaron dos motorreductores controlados mediante un puente H (L298N) para el movimiento del robot cartógrafo, despues de varias pruebas se decidio alimentar a los motores con 12V para que tuvieran un desempeño óptimo.
<p align="center">
  <img src="/Imagenes/DC.jpeg" align="center" width="400px" >
</p>

Para la implementación del puente H, se establecieron 5 posibles estados, los cuales permiten que el robot avance, gire o se detenga, en la siguiente tabla muestran las acciones de movimiento que se realizan de acuerdo al valor de las entradas del puente H.

 | Acción | S1 | S2 | S3 | S4 |
| ------------- | ------------- | ------------- |------------- |------------- |
| Avance | 0 | 1 | 1 | 0 |
| Retroceso | 1 | 0 | 0 | 1 |
| Giro Derecha | 1 | 0 | 1 | 0 |
| Giro Izquierda | 0 | 1 | 0 | 1 |
| Pausa | 0 | 0 | 0 | 0 | 



Teniendo en cuenta la anterior tabla se desarrollo el módulo [movimiento.v](/SoC_project/module/verilog/movimiento/) que cumple la función de driver para los motores. El diagrama que describe las conexiones de este driver con el periférico es el siguiente:

![Screenshot](/Imagenes/punteH.png)

Y la ubicación del registro en el mapa de memoria es:
```


```



El código utilizado para la realización del módulo es el siguiente:

```



```
      
El funcionamiento del módulo se basa en que según el valor de la señal de entrada **estado** se establecen los valores de los 4 pines de salida siguiendo la tabla descrita anteriormente para que los motores realicen la acción deseada. 
