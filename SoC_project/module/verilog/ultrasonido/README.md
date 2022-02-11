## Ultrasonido 🔊

Para el desarrollo de los drivers correspondientes a este periférico nos guiamos por el trabajo realizado por el Grupo 2 del semestre 2020-II ([Ultrasonido](https://github.com/unal-edigital2/w07_entrega-_final-grupo02/tree/main/Hardware/Modulos/ultrasonido)), en donde para determinar la distancia se utilizan principalmente dos módulos ([contador.v](/Soc_project/module/verilog/ultrasonido/contador.v) y [genpulsos.v](/Soc_project/module/verilog/ultrasonido/genpulsos.v)) junto a otros módulos auxiliares que cumplen la función de divisores de frecuencia para hacer relojes o se encargan de que se cumpla la máquina de estados. El diagrama que describe la conexión entre los drivers de este periférico es el siguiente (para más informacion remitase a [HC-SR04](/datasheets/HC-SR04.pdf)):

![Screenshot](/images/ultra_mem.png)

Y las ubicaciones de los registros en el mapa de memoria [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv) son las siguientes:

```
csr_base,ultrasonido_cntrl,0x82004800,,
```

El código utilizado para realizar este proceso es el siguiente: [ultrasonido.v](/SoC_project/module/verilog/ultrasonido/ultrasonido.v)
su funcionamiento se basa en una máquina de estados
