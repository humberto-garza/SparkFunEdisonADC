Intel Edison Sparkfun ADC Arduino Library
===================

[Back To Main](../README.md)

Index
=================

  * [Description](#description)
  * [References](#references)
  * [Information](#information)
  * [The Code](#the-code)
  * [Comments](#comments)


Description
===================
Library to get to use the SparkfunADC Edison Block from the Arduino IDE with or without the Arduino Edison Breakout board

References
===================
> - [How to write an Arduino Library](http://arduino.cc/en/Hacking/LibraryTutorial)

Information
===================
In order to add the library to your Arudino IDE try the following steps:
> - Sketch
> - Import Library...
> - Add Library
> - Navigate to the folder where you downloaded the **Spark_ADC.cpp** **Spark_ADC.h** files 
> - Select the folder called Spark_ADC
> - Click **Open**

**IMPORTANT!** Please **make sure** that the **cpp and h files** are the ones **from the Arduino folder**, the C++ cpp and h files will not work in the Arduino IDE, they were properly adapted!

That's it! Now you can see your library from within the Sketch->Import Library... menu! (It should be right at the end of that menu)
Just open the .ino file, upload your code and see in the Serial Monitor your ADC data popping out!

The Code
===================
> - First you have to specify the configuration bits according (For more reference take a look at the Description in the [Readme](../README.md) in the library section)
> - The configuration in the sample main  will read the AIN0 input in this range = [0, +2.048V]
> - It creates an object called ain0 and using the function **set_config_command()** it specifies its configuration
> - You can create as many objects as you want and also have different configurations for each, and when you read an specific object, it will read it with the desired configuration.
> - The function **get_config_command()** returns the specific linux command to setup the ADC 
> - After that, it only needs to call the **adc_read()** function in order to read the channel AIN0

Comments
===================
> - Make sure you select the right board and COM port
> - You will not need the Arduino Breakout board to make this file compile and upload in your Edison! If you get some issues try to Flashall.sh your board and try again, sometimes over the use and modifications this problem appears, or try these commands in your serial terminal:  
```
systemctl stop clloader
reboot
```

[Back To Top](#index)
