from Spark_ADC import Adc

ain0_operational_status = 				0b0
ain0_input_multiplexer_configuration = 			0b100
ain0_programmable_gain_amplifier_configuration =	0b010
ain0_device_operating_mode =				0b0
ain0_date_rate =					0b100
ain0_comparator_mode = 					0b0
ain0_compulator_polarity = 				0b0
ain0_latching_comparator	=			0b0
ain0_comparator_queue_and_disable =			0b11

pt1 = Adc()
pt1.set_config_command(
						ain0_operational_status, 
						ain0_input_multiplexer_configuration, 
						ain0_programmable_gain_amplifier_configuration, 
						ain0_device_operating_mode, 
						ain0_date_rate, 
						ain0_comparator_mode, 
						ain0_compulator_polarity, 
						ain0_latching_comparator,
						ain0_comparator_queue_and_disable
					  )

print pt1.command
while True:
	print pt1.adc_read()
