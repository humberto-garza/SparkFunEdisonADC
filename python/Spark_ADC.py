import fcntl, os

class Adc:

	def __init__( self, command = "i2cset -y 1 0x48 1 0x8344 w"):
		self.command = command

	def set_config_command(self, os, imc, pga, mode, rate, comp_mode, comp_pol, comp_lat, comp_que):
		rate = rate 			<< 13
		comp_mode = comp_mode 	<< 12
		comp_pol = comp_pol 	<< 11
		comp_lat = comp_lat 	<< 10
		comp_que = comp_que 	<< 8
		os = os 				<< 7
		imc = imc 				<< 4
		pga = pga 				<< 1
		#mode = mode 			<< 0 
		
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