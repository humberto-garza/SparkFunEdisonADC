Intel Edison Sparkfun ADC CPP Library
===================

[Back To Main](../README.md)

Index
=================

  * [Description](#description)
  * [Compilation](#compilation)
  * [Execution](#execution)
  * [The Code](#the-code)
  * [Information](#information)
  * [LICENSE](#license)
Description
===================
Library to get to use the SparkfunADC Edison using C++

Compilation
===================
To copile the main.cpp file just execute this command:

```
g++ main.cpp
```
This command will create an executable program called "a.out" (default executable target name).
You can change it if you want, follow this [reference](http://www.cs.fsu.edu/~jestes/howto/g++compiling.txt) for more information.

Execution
=================
To execute the program, execute these commands in the linux(yocto) command line (considering your output file is called "a.out"):

```
chmod +x a.out
./a.out
```
The Code
===================
> - This **main.cpp** creates a pair of objects (ain0 and ain1)
> - The code configures each object to work simultaneously and read the ADC according to the specific object
> - ain0 is configured to read the input AIN0 in this range: [0 to +2.048V]
> - ain1 is configured to read the input AIN1 in this range: [0 to +4.096V]
> - **set_config_command()** sets the string to configure the ADC to read the specific object
> - **get_config_command()** returns this linux command to configure the ADC and read the specific output
> - **adc_read()** returns the ADC reading that corresponds to the specific configuration string

Information
===================
If you need more information about the library, read the description found in the main folder

LICENSE
=================

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



[Back To Top](#intel-edison-sparkfun-adc-cpp-library)
