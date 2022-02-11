## Ultrasonido 🔊

![Screenshot](/images/ultra_mem.png)

Y las ubicaciones de los registros en el mapa de memoria [Soc_MemoryMap.csv](/SoC_project/Soc_MemoryMap.csv) son las siguientes:

```
csr_base,ultrasonido_cntrl,0x82004800,,
```

El código utilizado para realizar este proceso es el siguiente: [ultrasonido.v](/SoC_project/module/verilog/ultrasonido/ultrasonido.v) y su funcionamiento se basa en una máquina de estados y cuenta con 3: Start, Pulse, Echo, el código de esta máquina es el siguiente:

```
always @ (posedge clk_1MHz) begin
    case(status)
        Start:  begin
                    // Cuando init es 1, se reinician los registros.
                    if(init) begin
                        done = 0;
                        counter = 0;
                        distance = 0;
                        status = Pulse;
                    end
                end
        Pulse:  begin
                    // Trig cambia a 1 por 11 us, luego regresa 0.
                    trig = 1'b1;
                    counter = counter + 1'b1;
                    if(counter == 'd11) begin
                        trig = 0;
                        counter = 0;
                        status = Echo;
                    end
                end
        Echo:   begin
                    // Se espera a que echo sea 1, luego se contabiliza el tiempo hasta que echo sea 0.
                    if(echo) begin
                        echoStart = 1;
                        counter = counter + 1'b1;
                    end
                    if(echo == 0 && echoStart == 1) begin
                        // Si el contador es 0, se vuelve al estado anterior hasta que el resultado sea diferente a 0.
                        if(counter == 0) status = Pulse;
                        else begin
                            // Se divide el contador entre 58 para encontrar la distancia
                            distance = counter/'d58;
                            status = Start;
                            done = 1;
                        end
                    end
                end
    endcase 
end
```

En el estado Start se espera a la señal de inicialización init, con la cuál se reinician todos los registros de este módulo y se pasa al siguiente estado.

El siguiente estado es Pulse, en el cual se manda la señal de trig al periférico del ultrasonido, esta operación se realiza durante 11us, posterior a esto se pasa al siguiente estado.

Y finalmente, tenemos el estado Echo, el cual contabiliza el tiempo desde el cual se inicia la señal echo, hasta el momento en que esta es igual a 0, finalmente se procede a hallar la distancia dividiendo el valor que obtuvimos del contador entre 58, y acá se reinicia la máquina de estados pasando al estado inicial.
