/*
  Spark_ADC.h - Library for using the Sparkfun ADC BLock for Intel Edison+
  Created by Jose Humberto Garza Rosado, April 15, 2015.
  Released into the public domain.
*/

#ifndef Spark_ADC_h
#define Spark_ADC_h

#include <string>
#include "Arduino.h"

class Adc 
{
	public:
		Adc();
		void set_config_command(int os, int imc, int pga, int mode, int rate, int comp_mode, int comp_pol, int comp_lat, int comp_que);
		String get_config_command();
		int adc_read();

	private:
		std::string command;
};

#endif
