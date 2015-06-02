#include "mcu_api.h"
#include "mcu_errno.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//-----------------------------------------
/* the I2C address of ADC */
#define ACD_ADDRESS 0x48 //Check what address has the complete information up to now is only 0x48

//-----------------------------------------
/* the register address of the ADC register*/
#define ADC_REGISTER ((unsigned char)0x04) //ADC reads from 0x04

//-----------------------------------------
/*Global Variables*/
char buf[32];
int len;

//-----------------------------------------
int ADC_read()
{
	unsigned char bufv[3];
	int res;
	int x = 0x00;
	int aux = 0x00;

	res = i2c_read(ACD_ADDRESS, ADC_REGISTER, bufv, 2);

	if (res)
	{
		debug_print(DBG_ERROR, "ADC_send() FAILED!!!...");
	}
	else
	{
		int mask = 0b0111111111111;
		aux = bufv[1]&mask;
		x = aux>>4;
		aux = bufv[0] & mask;
		x += aux<<4;
		if (x > 0x07FF)
			x = x-4095;
	}

	char buf[60];
	//For some reason the "if (x > 0x07FF)" part of the code, will not work without the next line:
	int len = mcu_snprintf(buf, 60,"%X %X %X %X:::: ", bufv[0], bufv[1],aux, x);

	return x;
}

void mcu_main()
{
	int value;
	while(1)
	{
		value = ADC_read();
		len = mcu_snprintf(buf, 32,"%d\n",value);
		host_send((unsigned char*)buf, len);

		//This will prevent the atom from freezing
		mcu_sleep(1);
	}

}
