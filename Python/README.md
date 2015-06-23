Intel Edison Sparkfun ADC Python Library
===================

[Back To Main](../README.md)

Index
=================

  * [Description](#description)
  * [Execution](#execution)
  * [The Code](#the-code)
  * [Change the Configuration of the ADC Inputs](#change-the-configuration-of-the-adc-inputs)
   * [References](#references)
   * [Information](#information)
   * [Comments](#comments)
  * [LICENSE](#license)

Description
===================
Library to get to use the SparkfunADC Edison Block Using Python. 

Also, this library will help you get the configuration command in order to get it to work together with the MCU. [Here](#change-the-configuration-of-the-adc-inputs) is a description about how to get that **command**

Execution
===================
To execute the Python code you only need to do this from within the folder where both the **main.py** and the **Spark_ADC.py** files are located>
```
python main.py
```
	
The Code
=================
> - Similar to the Arduino sample code, this **main.py** file reads the AIN0 input from the ADC in this range: [0, +2.048V]
> - It creates an object called ain0 that will be used to read the ADC
> - You can create as many objects as you please to have different configurations, for example: have one to read AIN0, another to read AIN1 and another one to read the difference of AIN0-AIN1
> - It then prints the **linux command** that it uses to configure the ADC 
> - At the en it just prints what it reads from the ADC

___
Change the Configuration of the ADC Inputs
===================
This tutorial will help you modify the configuration command for the ADC 

References
=================
If you want to learn more about how this works, you can just go to the [Main Folder](https://github.com/humberto-garza/SparkFunEdisonADC) and go through the description bits information


Information
=================
> - To change the configuration just open the **config.py** file and change the variables displayed:
 - operational_status =						 0b0
 - input_multiplexer_configuration =			 0b100
 - programmable_gain_amplifier_configuration = 010
 - device_operating_mode =					 0b0
 - data_rate =								 0b100
 - comparator_mode = 							 0b0
 - compulator_polarity = 						 0b0
 - latching_comparator	=					 0b0
 - comparator_queue_and_disable =			 	 0b11

> - For example:
 - If you want to read only from the AIN0 you must change the **input_multiplexer_configuration** to **0b100**
 - If you want to read the difference of AIN0 and AIN3 you must change the **input_multiplexer_configuration** to **0b001**
 - If you want to change the samples per second to **128SPS** change the **data_rate** to **0b000**
 - If you want to change the Reference Voltage to **+-2.048V** you must change the **programmable_gain_amplifier_configuration** to **0b010**

> - Once You have modified the respective variables, just run the **config.py** and it will print the string to configure the ADC as you have specified, for example:
```
$python config.py
i2cset -y 1 0x48 1 0xe312 w
```
> - Now **i2cset -y 1 0x48 1 0xe312 w** can be executed in the command line to get the readings you specified.


Comments
=================
> - This configuration can be changed even while the MCU is running the reading.
> - If you are reading data from the MCU you just need to execute the returned command in the Atom to make sure you are reading what you want
> - Make sure that the **Spark_ADC.py** file is in the same folder

LICENSE
===================

Copyright (c) 2014, Intel Corporation
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
•	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
•	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
•	Neither the name of Intel Corporation nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

[Back To Top](#intel-edison-sparkfun-adc-python-library)
