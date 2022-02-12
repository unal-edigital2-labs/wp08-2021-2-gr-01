# Firmware 🚨
A continuacion se enunciara las funciones mas importantes para el desarrollo de software de este proyecto, las cuales son utilizadas para realizar pruebas en los perifericos y finalmente realizar una integracion total del funcionamiento de los mismos 

## Funciones de prueba de Modulos

### Medir distancia

La función "medir_distancia" es la encargada de al momento de ser llamada realizar una escritura en el registro de inicio del módulo de ultrasonido por lo que este provee una respuesta la cual es impresa, todo esto mediante el control de los botones 1 y 2 del dispositivo.

```
static int medir_distancia(void)
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

### Avanzar y Girar
Estas funciones están directamente relacionadas al funcionamiento del movimiento del dispositivo, pues estas permiten realizar un seguimiento de una línea en el suelo a partir del uso de los sensores infrarrojos, esta utiliza la lectura constante de los sensores infrarrojos ubicados en la parte inferior del dispositivo para modificar la dirección y realizar ajustes en los giros, además es la encargada de realizar pradas al momento de encontrar curvas o intersecciones.
```
static void avanzar(void)
{
	const int PararMotor = 0;
	const int AvanzarMotor = 1;
	const int IzquierdaMotor = 3;
	const int DerechaMotor = 4;
	_Bool L = infrarojo_cntrl_oL_read();
	_Bool LC = infrarojo_cntrl_oLC_read();
	_Bool C = infrarojo_cntrl_oC_read();
	_Bool RC = infrarojo_cntrl_oRC_read();
	_Bool R = infrarojo_cntrl_oR_read();

	while(L == 1 && R == 1)
	{
		movimiento_cntrl_estado_write(AvanzarMotor);
	}

	while(L == 0 && R == 0)
	{
		L = infrarojo_cntrl_oL_read();
		LC = infrarojo_cntrl_oLC_read();
		C = infrarojo_cntrl_oC_read();
		RC = infrarojo_cntrl_oRC_read();
		R = infrarojo_cntrl_oR_read();

		if(L == 0 && C == 1 && R == 0){
			movimiento_cntrl_estado_write(AvanzarMotor);
		}
		else if(L == 1 || LC == 1){
			movimiento_cntrl_estado_write(IzquierdaMotor);
		}
		else if(R == 1 || RC == 1){
			movimiento_cntrl_estado_write(DerechaMotor);
		}
	}
	movimiento_cntrl_estado_write(PararMotor);
}

static void girar(int direccion) 
{
	const int PararMotor = 0;
	const int IzquierdaMotor = 3;
	const int DerechaMotor = 4;

	switch (direccion)
	{
		case 1: movimiento_cntrl_estado_write(IzquierdaMotor);
			break;
		case 3: movimiento_cntrl_estado_write(DerechaMotor);
			break;
		case 0: movimiento_cntrl_estado_write(DerechaMotor);
				delay_ms(1000);
			break;
		default:movimiento_cntrl_estado_write(PararMotor);
			break;
	}

	delay_ms(500);

	while(infrarojo_cntrl_oC_read() == 0){}

	movimiento_cntrl_estado_write(PararMotor);
}
```

## Funciones de integracion

### Capitan
Esta función es la encargada de realizar una unión del módulo de ultrasonido con el módulo del servomotor, a partir de la lectura de los registros del módulo de ultrasonido la función se encarga de retornar la dirección a la que el dispositivo debería moverse, esto a partir de un pequeño algoritmo el cual se basa en tener un patrón de prioridad en las funciones, teniendo la como orden: Izquierda, Centro, Derecha. En caso de no tener camino libre, la función toma la decisión de realizar un giro de 180°. Este algoritmo permite que sin importar la forma y longitud del laberinto este siempre sea recorrido en su totalidad.
```
static int capitan(void)
{
//Dice en qué dirección ir
	const int CentroServo = 0;
	const int IzquierdaServo = 1;
	const int DerechaServo = 2;

	//Distancia para considerar camino libre
	int distLibre = 15;
	//Dirección en la que está libre
	int eleccion = 0; 

	//Girar en las 3 direcciones
	for (int i = 0; i <= 3; i++)
	{
		switch (i)
		{
		case 0: servomotor_cntrl_posicion_write(IzquierdaServo);
				eleccion = 1;
			break;
		case 1: servomotor_cntrl_posicion_write(CentroServo);
				eleccion = 2;
			break;
		case 2: servomotor_cntrl_posicion_write(DerechaServo);
				eleccion = 3;
			break;
		default:servomotor_cntrl_posicion_write(IzquierdaServo);
				eleccion = 0;
			break;
		}

		delay_ms(1000);

		if (medir_distancia() > distLibre) 
		{
			servomotor_cntrl_posicion_write(IzquierdaServo);
			return eleccion;	//Escoger direccion libre
		}
	}
}
```

### Ajuste X, Y y Orientacion
Las funciones “ajusteX”, “ajusteY”, “ajusteO” son las encargadas de realizar modificaciones en las coordenadas de posición actual del dispositivo pues estas varían con respecto a la dirección a la que se haya decidido avanzar y de la orientación a la que el carro se encuentre en ese momento por lo que es necesario realizar este ajuste.
```
static int ajusteX(int orientacion, int direccion, int Xactual)
{
	const int norte = 0;
	const int sur = 1;
	const int este = 2;
	const int oeste = 3;
	const int izquierda = 1;
	const int centro = 2;
	const int derecha = 3;
	const int atras = 0;
	switch (orientacion)
	{
	case norte:	Xactual = (direccion == derecha) ? Xactual+1: Xactual;
				Xactual = (direccion == izquierda) ? Xactual-1: Xactual;
			break;
	case sur: 	Xactual = (direccion == derecha) ? Xactual-1: Xactual;
				Xactual = (direccion == izquierda) ? Xactual+1: Xactual;
			break;
	case este: 	Xactual = (direccion == centro) ? Xactual+1: Xactual;
				Xactual = (direccion == atras) ? Xactual-1: Xactual;
			break;
	case oeste: Xactual = (direccion == centro) ? Xactual-1: Xactual;
				Xactual = (direccion == atras) ? Xactual+1: Xactual;
			break;
	}
	return Xactual;
}
```

### Integracion
Finalmente la función “integración” permite realizar la unión de todas las funciones mencionadas anteriormente, esta inicia con la creación de una matriz de 10x10, así como del establecimiento de las variables que almacena la ubicación actual y la ubicación inicial del dispositivo. Después a partir del uso de la función “Capitán” se decide qué dirección debe tomar a continuación el dispositivo, posteriormente las funciones de movimiento se encargan de realizar dicha acción. Finalmente se realiza el ajuste de las variables de posición con respecto al movimiento realizado. Se concluye con la impresión de la matriz del mapa que denota al laberinto.
```
static void integracion(void)
{
	const int norte = 0;
	const int sur = 1;
	const int este = 2;
	const int oeste = 3;
	const int izquierda = 1;
	const int centro = 2;
	const int derecha = 3;
	const int atras = 0;

	int mapa[10][10];
	_Bool recorrido = 0;
	_Bool finalizacion = 0;
	int Xinicial = 1, Yinicial = 1;
	int Xactual = Xinicial, Yactual = Yinicial;
	int orientacion = sur;
	int direccion = centro; 

	//Inicialización de la matriz del laberinto
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){  
			mapa[i][j] = 0;
		}    
	}
	for(int i=0; i<10; i++){  
		mapa[i][0] = i;
	}
	for(int j=0; j<10; j++){  
		mapa[0][j] = j;
	}
	Xactual = Xinicial;
	Yactual = Yinicial;
	mapa[Yactual][Xactual] = 1;

	//Imprecion de la matriz del laberinto
	print("%i |", mapa[0][0]);
	for(int j=1; j<10; j++){  
		printf("%i  ", mapa[0][j]);
	}
	printf("\n-------------------------------\n");
	for(int i=1; i<10; i++){
		printf("%i |", mapa[i][0]);
		for(int j=1; j<10; j++){  
			printf("%i  ", mapa[i][j]);
		}
		printf("\n");
	}

	while(!(buttons_in_read()&1))
	{
		recorrido = (buttons_in_read()&(1<<1)) ? 1 : 0;
		finalizacion = 0;
		while (recorrido)
		{
			direccion = capitan();
			girar(direccion);
			avanzar();

			Xactual = ajusteX(orientacion, direccion, Xactual);
			Yactual = ajusteX(orientacion, direccion, Yactual);
			orientacion = ajusteO(orientacion, direccion);
			
			mapa[Yactual][Xactual] = 1;

			recorrido = ((Xactual == Xinicial)&&(Yactual == Yinicial)) ? 0 : 1;
			finalizacion = ((Xactual == Xinicial)&&(Yactual == Yinicial)) ? 1 : 0;
		}
		while (finalizacion)
		{
			servomotor_cntrl_posicion_read(1);
			delay_ms(1000);
			servomotor_cntrl_posicion_read(2);
			if (buttons_in_read()&(1<<1)){
				//Imprecion de la matriz del laberinto
				print("%i |", mapa[0][0]);
				for(int j=1; j<10; j++){  
					printf("%i  ", mapa[0][j]);
				}
				printf("\n-------------------------------\n");
				for(int i=1; i<10; i++){
					printf("%i |", mapa[i][0])
					for(int j=1; j<10; j++){  
						printf("%i  ", mapa[i][j]);
					}
					printf("\n");
				}
				finalizacion = 0;
			}
		}
	}
}
```
