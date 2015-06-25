/*
Copyright (c) 2015, Intel Corporation

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Created by Jose Humberto Garza Rosado
gcc main.cpp -lmraa -L../usr/lib/
*/
//////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include "Spark_ADC.h"
#include "Spark_ADC.cpp"

#include "mraa.hpp"
using namespace std;

//////////////////////////////////////////////////////////////////
// Global Variables
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Global Constants
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int ain1_operational_status = 							0b0;
	int ain1_input_multiplexer_configuration = 				0b000;
	int ain1_programmable_gain_amplifier_configuration =	0b010;
	int ain1_device_operating_mode =						0b0;
	int ain1_date_rate =									0b100;
	int ain1_comparator_mode = 								0b0;
	int ain1_compulator_polarity = 							0b0;
	int ain1_latching_comparator	=						0b0;
	int ain1_comparator_queue_and_disable =					0b11;
	
	Adc ain1(1, 0x48);

	ain1.set_config_command(
				ain1_operational_status, 
				ain1_input_multiplexer_configuration, 
				ain1_programmable_gain_amplifier_configuration, 
				ain1_device_operating_mode, 
				ain1_date_rate, 
				ain1_comparator_mode, 
				ain1_compulator_polarity, 
				ain1_latching_comparator,
				ain1_comparator_queue_and_disable
				);

	cout<<ain1.get_config_command()<<endl;
	
	int x =0;
	while(x < 1000) //0.79 seconds
	{
		cout<<ain1.adc_read()<<endl;
		x++;
	}	

	return 0;
}
