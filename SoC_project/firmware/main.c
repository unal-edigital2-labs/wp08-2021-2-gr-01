#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>

#include "delay.h"
#include "display.h"

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}
	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("led                             - led test");
	puts("switch                          - switch test");
	puts("display                         - display test");
	puts("rgbled                          - rgb led test");
	puts("vga                             - vga test");
	puts("*movimiento                      - movimiento test");
	puts("*servomotor                      - servomotor test");
	puts("*ultrasonido                     - ultrasonido test");
	puts("*infrarojo                       - infrarojo test");
	puts("*Avanzar                         - avanzar_test");
}

static void reboot(void)
{
	ctrl_reset_write(1);
}


static void led_test(void)
{
	unsigned int i;
	printf("Test del los leds... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {
		for(i=1; i<65536; i=i*2) {
			leds_out_write(i);
			delay_ms(50);
		}
		for(i=32768;i>1; i=i/2) {
			leds_out_write(i);
			delay_ms(50);
		}
	}	
}

static void switch_test(void)
{
	unsigned short temp2 = 0;
	printf("Test del los interruptores... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {
		unsigned short temp = switchs_in_read();
		if (temp2 != temp){
			printf("switch bus : %i\n", temp);
			leds_out_write(temp);
			temp2 = temp;
		}
	}
}

static void display_test(void)
{
	int i;
	signed char defill = 0;	//1->left, -1->right, 0->.
	
	char txtToDisplay[40] = {0, DISPLAY_0, DISPLAY_1,DISPLAY_2,DISPLAY_3,DISPLAY_4,DISPLAY_5,DISPLAY_6,DISPLAY_7,DISPLAY_8,DISPLAY_9,DISPLAY_A,DISPLAY_B,DISPLAY_C,DISPLAY_D,DISPLAY_E,DISPLAY_F,DISPLAY_G,DISPLAY_H,DISPLAY_I,DISPLAY_J,DISPLAY_K,DISPLAY_L,DISPLAY_M,DISPLAY_N,DISPLAY_O,DISPLAY_P,DISPLAY_Q,DISPLAY_R,DISPLAY_S,DISPLAY_T,DISPLAY_U,DISPLAY_V,DISPLAY_W,DISPLAY_X,DISPLAY_Y,DISPLAY_Z,DISPLAY_DP,DISPLAY_TR,DISPLAY_UR};
	
	printf("Test del los display de 7 segmentos... se interrumpe con el botton 1\n");

	while(!(buttons_in_read()&1)) {
		display(txtToDisplay);
		if(buttons_in_read()&(1<<1)) defill = ((defill<=-1) ? -1 : defill-1);
		if(buttons_in_read()&(1<<2)) defill = ((defill>=1) ? 1 : defill+1);
		if (defill > 0) {
			char tmp = txtToDisplay[0];
			for(i=0; i<sizeof(txtToDisplay)/sizeof(txtToDisplay[i]); i++) {
				txtToDisplay[i] = ((i==sizeof(txtToDisplay)/sizeof(txtToDisplay[i])-1) ? tmp : txtToDisplay[i+1]);
			}
		}
		else if(defill < 0) {
			char tmp = txtToDisplay[sizeof(txtToDisplay)/sizeof(txtToDisplay[0])-1];
			for(i=sizeof(txtToDisplay)/sizeof(txtToDisplay[i])-1; i>=0; i--) {
				txtToDisplay[i] = ((i==0) ? tmp : txtToDisplay[i-1]);
			}
		}
		delay_ms(500);
	}
}

static void rgbled_test(void)
{
	unsigned int T = 128;
	
	ledRGB_1_r_period_write(T);
	ledRGB_1_g_period_write(T);
	ledRGB_1_b_period_write(T);

	ledRGB_1_r_enable_write(1);
	ledRGB_1_g_enable_write(1);
	ledRGB_1_b_enable_write(1);

	ledRGB_2_r_period_write(T);
	ledRGB_2_g_period_write(T);
	ledRGB_2_b_period_write(T);
		
	ledRGB_2_r_enable_write(1);
	ledRGB_2_g_enable_write(1);
	ledRGB_2_b_enable_write(1);

	for (unsigned int j=0; j<100; j++){
		ledRGB_1_g_width_write(j);
		for (unsigned int i=0; i<100; i++){
			ledRGB_1_r_width_write(100-i);
			ledRGB_1_b_width_write(i);	
			delay_ms(20);
		}	
	}
}

static void vga_test(void)
{
	int x,y;
	
	for(y=0; y<480; y++) {
		for(x=0; x<640; x++) {
			vga_cntrl_mem_we_write(0);
			vga_cntrl_mem_adr_write(y*640+x);
			if(x<640/3)	
				vga_cntrl_mem_data_w_write(((int)(x/10)%2^(int)(y/10)%2)*15);
			else if(x<2*640/3) 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<4);
			else 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<8);
			vga_cntrl_mem_we_write(1);
		}
	}
}



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

/* static int camara(void)
{
	unsigned int col = 0;
	unsigned int done = 0;
	unsigned int error = 0;
	camara_cntrl_init_write(1);
	delay_ms(10);
	while (1)
	{
		col = camara_cntrl_res_read(); 
		done = camara_cntrl_done_read();
		error = camara_cntrl_error_read();
		if(done){
			camara_cntrl_init_write(0);
			if(!error){
				return col;
			}
		}
	}
} */



static void movimiento_test(void)
{
	const int Parar = 0;
	const int Avanzar = 1;
	const int Retroceder = 2;
	const int Izquierda = 3;
	const int Derecha = 4; 
	movimiento_cntrl_estado_write(Avanzar);
	delay_ms(400);
	movimiento_cntrl_estado_write(Parar);
	delay_ms(1000);
	movimiento_cntrl_estado_write(Retroceder);
	delay_ms(400);
	movimiento_cntrl_estado_write(Parar);
	delay_ms(1000);
	movimiento_cntrl_estado_write(Izquierda);
	delay_ms(700);
	movimiento_cntrl_estado_write(Parar);
	delay_ms(1000);
	movimiento_cntrl_estado_write(Derecha);
	delay_ms(700);
	movimiento_cntrl_estado_write(Parar);
	delay_ms(1000);
	movimiento_cntrl_estado_write(Derecha);
	delay_ms(1400);
	movimiento_cntrl_estado_write(Parar);
}

static void servomotor_test(void)
{
	const int Centro = 0;
	const int Izquierda = 1;
	const int Derecha = 2;
	servomotor_cntrl_posicion_write(Centro);
	delay_ms(1000);
	servomotor_cntrl_posicion_write(Izquierda);
	delay_ms(1000);
	servomotor_cntrl_posicion_write(Derecha);
	delay_ms(1000);
	servomotor_cntrl_posicion_write(3);
}

static void ultrasonido_test(void)
{
	int d = 0;
	printf("Test de Modulo de Ultrasonido. Para activar oprimir botton 2.\n Para interrumpir oprimir el botton 1.\n");
	while(!(buttons_in_read()&1)){
		if(buttons_in_read()&(1<<1)){ 
			d = medir_distancia();
			printf("%d \n", d);
		}
	}
}

static void infrarojo_test(void)
{
	printf("Test de Modulo de Infrarojo. Para interrumpir oprimir el botton 1\n");
	while(!(buttons_in_read()&1))
	{
		_Bool L = infrarojo_cntrl_oL_read();
		_Bool LC = infrarojo_cntrl_oLC_read();
		_Bool C = infrarojo_cntrl_oC_read();
		_Bool RC = infrarojo_cntrl_oRC_read();
		_Bool R = infrarojo_cntrl_oR_read();

		_Bool IR[5] = {L, LC, C, RC, R};

		for(int i = 0; i<5; i++){
			printf("%i, ", IR[i]);
		}
		printf("\n");
	}
}

static void avanzar_test(void)
{
	while(!(buttons_in_read()&1)){
		if(buttons_in_read()&(1<<1)){ 
			avanzar();

			servomotor_test();

			avanzar();

			servomotor_test();

			girar(3);

			avanzar();
			
			servomotor_test();

			girar(3);

			avanzar();

			servomotor_test();

			girar(0);

			avanzar();
			
			servomotor_test();

			girar(1);

			avanzar();
			
			servomotor_test();

			girar(1);

			avanzar();
			
			servomotor_test();

			girar(0);
		}
	}
}

/* static void camara_test(void)
{	
	int color = camara();
	delay_ms(10);
	switch (color)
	{
	case 1: printf("Azul \n");
		break;
	case 2: printf("Verde \n");
		break;
	case 4: printf("Rojo \n");
		break;
	case 0: printf("Ninguno \n");
		break;
	default:printf("._.\n");
		break;
	}
} */



static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	else if(strcmp(token, "led") == 0)
		led_test();
	else if(strcmp(token, "switch") == 0)
		switch_test();
	else if(strcmp(token, "display") == 0)
		display_test();
	else if(strcmp(token, "rgbled") == 0)
		rgbled_test();
	else if(strcmp(token, "vga") == 0)
		vga_test();
	else if(strcmp(token, "movimiento") == 0)
		movimiento_test();
	else if(strcmp(token, "servomotor") == 0)
		servomotor_test();
	else if(strcmp(token, "ultrasonido") == 0)
		ultrasonido_test();
	else if(strcmp(token, "infrarojo") == 0)
		infrarojo_test();
	else if(strcmp(token, "avanzar") == 0)
		avanzar_test();
	/* else if(strcmp(token, "camara") == 0)
		camara_test(); */
	prompt();
}


int main(void)
{
	irq_setmask(0);
	irq_setie(1);

	uart_init();

	puts("\nSoC - RiscV project UNAL 2021-2 Grupo 1 :D-- CPU testing software built "__DATE__" "__TIME__"\n");
	help();
	prompt();

	while(1){
		console_service();
	}

	return 0;
}
