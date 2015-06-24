/*
Copyright (c) 2014, Intel Corporation

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
*/

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



