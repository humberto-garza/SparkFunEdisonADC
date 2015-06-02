Intel Edison SparkfunADC MCU Function
===================

Description
-------------
This function will read the values from the ADC and send them to the Atom through the **/dev/ttymcu01** file
Be careful to follow these steps and diagrams to setup your board correctly

----------

References
-------------
> - If you want to know more about the Intel Edison MCU Quark processor, you can go to this site and learn more about it: (Microcontroller MCU Setup Guide)[https://software.intel.com/en-us/creating-applications-with-mcu-sdk-for-intel-edison-board]

----------

Seting Up
-------------
Follow thos diagram to make the right connections:
![alt tag]()

----------

Information
-------------
Follow These steps:
> - Once you have setup the Eclipse IDE to program your MCU and make sure it works, paste the code provided **muc_ADC.c** in a new MCU project
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

----------

Comments
-------------
> - Make sure that the MCU IDE is working with your board correctly before you try this code.
> - This sample code will work for this configuration, if you want to use different configurations for the ADC inputs, you can just change this command **"i2cset -y 1 0x48 1 0xe312 w"** 
> - Specifically you need to change the 0xe312 part
> - If you need some help to change the command to the desired configuration, go to the Python (folder)[https://github.com/humberto-garza/SparkFunEdisonADC/tree/master/python] to get some help.

----------
