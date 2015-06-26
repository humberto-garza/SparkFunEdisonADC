# Copyright (c) 2015, Intel Corporation

# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:

# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# * Neither the name of Intel Corporation nor the names of its contributors
#   may be used to endorse or promote products derived from this software
#   without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Created by Jose Humberto Garza Rosado

# ///////////////////////////////////////////////////////////////////
# //Set up the ADC register by sending the next bits:
# //*Represents the suggested configuration to only read from A1N0

# //int os:       Operational status/single-shot conversion start.
# //          This bit determines the operational status of the device.
# //          This bit can only be written when in power-down mode.
# //          Write status:
# //            0b0: No Effect.
# //            0b1: Begin single conversion (when in power-down mode).* 
# //          Read status
# //            0b0: Device is currently performing a conversion.
# //            0b1: Device is not currently performing a conversion.

# //int imc:      Input multiplexer configuration.
# //          These bits configure the input multiplexer.
# //          VIN (AINX minus AINY):
# //            0b000: AIN0 - AIN1
# //            0b001: AIN0 - AIN3
# //            0b010: AIN1 - AIN3
# //            0b011: AIN2 - AIN3
# //            0b100: AIN0 - GND*  
# //            0b101: AIN1 - GND
# //            0b110: AIN2 - GND
# //            0b111: AIN3 - GND

# //int pga:      Programmable gain amplifier configuration
# //          These bits configure the programmable gain amplifier. 
# //          FS:
# //            0b000: +-6.144V
# //            0b001: +-4.096V*
# //            0b010: +-2.048V
# //            0b011: +-1.024V
# //            0b100: +-0.512V
# //            0b101: +-0.256V
# //            0b110: +-0.256V
# //            0b111: +-0.256V

# //int mode:     Device operating mode
# //          This bit controls the current operational mode: 
# //            0b0: Continuous conversion mode.*
# //            0b1: Power-Down single-shot mode.

# //int rate:     Data rate
# //          These bits control the data rate setting:
# //            0b000: 128SPS
# //            0b001: 250SPS
# //            0b010: 490SPS
# //            0b011: 920SPS
# //            0b100: 1600SPS*
# //            0b101: 2400SPS
# //            0b110: 3300SPS
# //            0b111: 3300SPS

# //int comp_mode:  Comparator mode
# //          This bit controls the comparator mode of operation.
# //          It changes whether the comparator is implemented as a traditional comparator 
# //          or as a window comparator:
# //            0b0: Traditional comparator with hysteresis.*
# //            0b1: Window comparator.

# //int comp_pol:   Comparator polarity
# //          This but controls the polarity of the ALERT/RDY pin:
# //            0b0: Comparator output is active low.*
# //            0b1: ALERT/RDY pin is active high.

# //int comp_lat:   Latching comparator
# //          This bit controls whether the ALERT/RDY pin latches once asserted or clears once
# //          conversions are within the margin of the upper and lower threshold values:
# //            0b0: The comparator output is active low.*
# //            0b1: ALERT/RDY pin is active high.            

# //int comp_que:   Comparator queue and disable 
# //          These bits perform two functions:
# //            0b11: Disable the comparator function and put the ALERT/RDY pin into a high state.*
# //              Otherwise they control the number of successive conversions exceeding the upper or
# //              lower thresholds required before asserting the ALERT/RDY pin.
# //            0b00: Assert after one conversion.
# //            0b01: Assert after two conversions.
# //            0b10: Assert after four conversions.

import fcntl, os

class Adc:

	def __init__( self, command = "i2cset -y 1 0x48 1 0x8344 w"):
		self.command = command

	def set_config_command(self, os, imc, pga, mode, rate, comp_mode, comp_pol, comp_lat, comp_que):
		rate = rate 		<< 13
		comp_mode = comp_mode 	<< 12
		comp_pol = comp_pol 	<< 11
		comp_lat = comp_lat 	<< 10
		comp_que = comp_que 	<< 8
		os = os 		<< 7
		imc = imc 		<< 4
		pga = pga 		<< 1
		#mode = mode 		<< 0 
		total = os + imc + pga + mode + rate + comp_mode + comp_pol + comp_lat + comp_que
		self.command = "i2cset -y 1 0x48 1 " + hex(total) + " w"

	def adc_read(self):
		os.system(self.command)
		adc = os.popen("i2cget -y 1 0x48 0 w")
    		value = adc.read()
    		concat = value[0]+value[1]+value[3]+value[4]+value[5]+value[2]
    		x = int(concat,16)
    		os.close
    		if x > 0x7FF:
    			return -1*((0x7FF*2+2)+(~x))
    		else:
    			return x

	def __del__(self):
		class_name = self.__class__.__name__
		print class_name, "destroyed"
