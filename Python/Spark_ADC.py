# Copyright (c) 2014, Intel Corporation
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
# • Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# • Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
# • Neither the name of Intel Corporation nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Library for the Sparkfun ADC BLock for Intel Edison
# Created by Jose Humberto Garza Rosado

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
