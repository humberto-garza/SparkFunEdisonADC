Intel Edison SparkfunADC Arduino Library
===================

[Back To Index](./SparkFunEdisonADC)

Description
-------------
Library to get to use the SparkfunADC Edison Block from the Arduino IDE with or without the Arduino Edison Breakout board

----------

References
-------------
> - [How to write an Arduino Library](http://arduino.cc/en/Hacking/LibraryTutorial)

----------

Information
-------------
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


----------

Comments
-------------
> - Make sure you select the right board and COM port
> - You will not need the Arduino Breakout board to make this file compile and upload in your Edison! If you get some issues try to Flashall.sh your board and try again, sometimes over the use and modifications this problem appears, or try these commands in your serial terminal:  
```
systemctl stop clloader
reboot
```
----------
