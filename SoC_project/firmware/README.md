# Firmware 🚨
A continuacion se enunciara las funciones mas importantes para el desarrollo de software de este proyecto, las cuales son utilizadas para realizar pruebas en los perifericos y finalmente realizar una integracion total del funcionamiento de los mismos 

## Medir distancia

La función "medir_distancia" es la encargada de al momento de ser llamada realizar una escritura en el registro de inicio del módulo de ultrasonido por lo que este provee una respuesta la cual es impresa, todo esto mediante el control de los botones 1 y 2 del dispositivo.

```static int medir_distancia(void)
{
	ultrasonido_cntrl_init_write(1);
	delay_ms(2);
	while(1){
		if(ultrasonido_cntrl_done_read() == 1){
			int distancia = ultrasonido_cntrl_distance_read();
			ultrasonido_cntrl_init_write(0);
			return distancia;
		}
	}
}
```
A continuación podemos observar el diagrama de bloques que describe la conexión del periférico de los sensores infrarrojos en nuestro proyecto, esto es posible gracias al módulo ([infrarrojo.py](/SoC_project/module/infrarojo.py)) que obtiene un espacio de memoria gracias al modulo general de ([buildSoCproject.py](/SoC_project/buildSoCproject.py))   

![Screenshot](/images/infrar_mem.png)

Por ultimo vemos su espacio de memoria dentro del archivo [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv)

```
csr_base,infrarojo_cntrl,0x82005000,,
```
