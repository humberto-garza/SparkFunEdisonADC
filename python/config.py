from Spark_ADC import Adc

operational_status = 				0b0
input_multiplexer_configuration = 			0b100
programmable_gain_amplifier_configuration =	0b010
device_operating_mode =				0b0
data_rate =					0b100
comparator_mode = 					0b0
compulator_polarity = 				0b0
latching_comparator	=			0b0
comparator_queue_and_disable =			0b11

pt1 = Adc()
pt1.set_config_command(
						operational_status, 
						input_multiplexer_configuration, 
						programmable_gain_amplifier_configuration, 
						device_operating_mode, 
						date_rate, 
						comparator_mode, 
						compulator_polarity, 
						latching_comparator,
						comparator_queue_and_disable
					  )

print pt1.command