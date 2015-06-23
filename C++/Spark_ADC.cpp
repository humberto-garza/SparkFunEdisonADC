/*
Copyright (c) 2014, Intel Corporation
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
• Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
• Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
• Neither the name of Intel Corporation nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Library for the Sparkfun ADC BLock for Intel Edison
Created by Jose Humberto Garza Rosado
*/
//////////////////////////////////////////////////////////////////
#include "Spark_ADC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//Constructor
//Use this default configuration: 0x0 0x100 0x010 0x0 0x100 0x0 0x0 0x0 0x11
Adc::Adc() 
{
	command = "i2cset -y 1 0x48 1 0x8344 w";
}
///////////////////////////////////////////////////////////////////
//Set up the ADC register by sending the next bits:
//*Represents the suggested configuration to only read from A1N0

//int os: 			Operational status/single-shot conversion start.
//					This bit determines the operational status of the device.
//					This bit can only be written when in power-down mode.
//					Write status:
//						0x0: No Effect.
//						0x1: Begin single conversion (when in power-down mode).* 
//					Read status
//						0x0: Device is currently performing a conversion.
//						0x1: Device is not currently performing a conversion.

//int imc:			Input multiplexer configuration.
//					These bits configure the input multiplexer.
//					VIN (AINX minus AINY):
//						0x000: AIN0 - AIN1
//						0x001: AIN0 - AIN3
//						0x010: AIN1 - AIN3
//						0x011: AIN2 - AIN3
//						0x100: AIN0 - GND* 	
//						0x101: AIN1 - GND
//						0x110: AIN2 - GND
//						0x111: AIN3 - GND

//int pga:			Programmable gain amplifier configuration
//					These bits configure the programmable gain amplifier. 
//					FS:
//						0x000: +-6.144V
//						0x001: +-4.096V*
//						0x010: +-2.048V
//						0x011: +-1.024V
//						0x100: +-0.512V
//						0x101: +-0.256V
//						0x110: +-0.256V
//						0x111: +-0.256V

//int mode:			Device operating mode
//					This bit controls the current operational mode:	
//						0x0: Continuous conversion mode.*
//						0x1: Power-Down single-shot mode.

//int rate:			Data rate
//					These bits control the data rate setting:
//						0x000: 128SPS
//						0x001: 250SPS
//						0x010: 490SPS
//						0x011: 920SPS
//						0x100: 1600SPS*
//						0x101: 2400SPS
//						0x110: 3300SPS
//						0x111: 3300SPS

//int comp_mode: 	Comparator mode
//					This bit controls the comparator mode of operation.
//					It changes whether the comparator is implemented as a traditional comparator 
//					or as a window comparator:
//						0x0: Traditional comparator with hysteresis.*
//						0x1: Window comparator.

//int comp_pol:		Comparator polarity
//					This but controls the polarity of the ALERT/RDY pin:
//						0x0: Comparator output is active low.*
//						0x1: ALERT/RDY pin is active high.

//int comp_lat:		Latching comparator
//					This bit controls whether the ALERT/RDY pin latches once asserted or clears once
//					conversions are within the margin of the upper and lower threshold values:
//						0x0: The comparator output is active low.*
//						0x1: ALERT/RDY pin is active high.						

//int comp_que:		Comparator queue and disable 
//					These bits perform two functions:
//						0x11: Disable the comparator function and put the ALERT/RDY pin into a high state.*
//							Otherwise they control the number of successive conversions exceeding the upper or
//							lower thresholds required before asserting the ALERT/RDY pin.
//						0x00: Assert after one conversion.
//						0x01: Assert after two conversions.
//						0x10: Assert after four conversions.

void Adc::set_config_command(int os, int imc, int pga, int mode, int rate, int comp_mode, int comp_pol, int comp_lat, int comp_que)
{
	comp_mode = comp_mode << 12;
	comp_pol = comp_pol << 11;
	comp_lat = comp_lat << 10;
	comp_que = comp_que << 8;
	os = os << 7;
	imc = imc << 4;
	pga = pga << 1;
	//mode = mode << 0 ;
	rate = rate << 13;
	int total = os + imc + pga + mode + rate + comp_mode + comp_pol + comp_lat + comp_que;
	
	char numx[256];
	sprintf(numx,"0x%X",total);
	command = numx;
	command = "i2cset -y 1 0x48 1 " + command + " w";
}


///////////////////////////////////////////////////////////////////
// Read from the I2C device
// Returns an the value, and a -1 in case it could not read the device
int Adc::adc_read()
{
	system(command.c_str());
	char buffer[10];
	string result = "";
	//i2cset -y 1 0x48 1 0x8344 w
	FILE* fpipe = popen("i2cget -y 1 0x48 0 w", "r");
	if (not fpipe) 
	{
		pclose(fpipe);
	    return -1;
	}	
	else
	{
		std::fgets(buffer, sizeof buffer, fpipe);
		result += buffer[0]; //0
		result += buffer[1]; //x 
		result += buffer[3]; //0
		result += buffer[4];
		result += buffer[5];
		result += buffer[2];

		unsigned int x = strtol(result.c_str(), NULL, 16);
		pclose(fpipe);
		if(x > 0x7FF)
		{
			int aux =  -1*(~x-0xFFFFF000);
			return aux;
		}
		else
			return  x;
	}
}

///////////////////////////////////////////////////////////////////
// Read the object's command 
string Adc::get_config_command()
{
	return command;
}
