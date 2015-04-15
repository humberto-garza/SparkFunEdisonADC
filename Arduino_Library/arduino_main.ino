#include <Spark_ADC.h>
#include <string>
Adc ain0;

void setup() {
  //start serial connection
  Serial.begin(9600);
  
}

// the loop routine runs over and over again forever:
void loop() {

  int ain0_operational_status =                         0b0;
  int ain0_input_multiplexer_configuration =            0b100;
  int ain0_programmable_gain_amplifier_configuration =  0b010;
  int ain0_device_operating_mode =                      0b0;
  int ain0_date_rate =                                  0b100;
  int ain0_comparator_mode =                            0b0;
  int ain0_compulator_polarity =                        0b0;
  int ain0_latching_comparator  =                       0b0;
  int ain0_comparator_queue_and_disable =               0b11;

  
  ain0.set_config_command(
            ain0_operational_status, 
            ain0_input_multiplexer_configuration, 
            ain0_programmable_gain_amplifier_configuration, 
            ain0_device_operating_mode, 
            ain0_date_rate, 
            ain0_comparator_mode, 
            ain0_compulator_polarity, 
            ain0_latching_comparator,
            ain0_comparator_queue_and_disable
            );
            
  Serial.println(ain0.get_config_command());
  while(1)
  { 
    Serial.println(ain0.adc_read());
    delay(300);        // delay in between reads for stability
  }
 
}



