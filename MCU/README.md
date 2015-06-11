Intel Edison Sparkfun ADC MCU Function
===================

[Back To Main](../README.md)

Index
=================

  * [Description](#description)
  * [References](#references)
  * [Setting Up](#setting-up)
  * [Information](#information)
  * [The code](#the-code)
  * [Comments](#comments)

Description
=================
This function will read the values from the ADC and send them to the Atom through the **/dev/ttymcu01** file
Be careful to follow these steps and diagrams to setup your board correctly

References
=================
> - If you want to know more about the Intel Edison MCU Quark processor, you can go to this site and learn more about it: [Microcontroller MCU Setup Guide](https://software.intel.com/en-us/creating-applications-with-mcu-sdk-for-intel-edison-board)

Setting Up
=================
Follow this diagram to make the right connections:
![alt tag](https://github.com/humberto-garza/SparkFunEdisonADC/blob/master/Diagrams/Sketch_MCU_ADC.jpg)

Information
=================
Follow These steps:
> - Once you have setup the Eclipse IDE to program your MCU and make sure it works, paste the code provided **mcu_ADC.c** in a new MCU project
> - Make sure to save the project before proceeding 
> - Go to **Project>Clean** and clean all
> - Go to **MCU>Build Project**
> - Go to **MCU>Download**
> - Now all you have to do is run the Script provided **setup_I2C_MCU.sh** and it will just **cat dev/ttymcu0** this file in order to see what is being sent from the MCU coming from the ADC
> - To run the script do as follows:

```
chmod +x setup_I2C_MCU.sh
./setup_I2C_MCU.sh
```

The Code
=================
> - The Function **ADC_read()** returns the value read by the ADC according to the configuration set, it returns an int with the value read scalated 
> - The value read is sent to the Atom using the file **/dev/ttymcu0**

Comments
=================
> - Make sure that the MCU IDE is working with your board correctly before you try this code.
> - This sample code will work for this configuration, if you want to use different configurations for the ADC inputs, you can just change this command **"i2cset -y 1 0x48 1 0xe312 w"** 
> - Specifically you need to change the **0xe312** part
> - If you need some help to change the command to the desired configuration, go to the  [Python Folder](../Python/README.md) to get some help.
> - If you read the ADC while the MCU is communicating with it, you will get some **Reading Errors**, so make sure that you are only using it with either the Atom or the MCU, never at the same time.

[Back To Top](#intel-edison-sparkfun-adc-mcu-function)
