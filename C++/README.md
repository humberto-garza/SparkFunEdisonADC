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

[Back To Top](#intel-edison-sparkfun-adc-cpp-library)
