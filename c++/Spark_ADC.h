#ifndef SPARK_ADC_H
#define SPARK_ADC_H

#include <string.h>
#include <iostream>

typedef unsigned char byte;
class Adc 
{
	public:
		Adc();
		//~Adc();	//Destructor 
		void set_config_command(int os, int imc, int pga, int mode, int rate, int comp_mode, int comp_pol, int comp_lat, int comp_que);
		std::string get_config_command();
		int adc_read();

	private:
		std::string command;

};

#endif

