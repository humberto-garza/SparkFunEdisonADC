Intel Edison Linksprite Infrared Camera Library
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
C library to get to use the Linsprite UART Infrared Camera 

Compilation
===================
To copile the main.c file just execute this command:

```
g++ main.c -o main.out
```
This command will create an executable program called "main.out".

You can change it if you want, follow this [reference](http://www.cs.fsu.edu/~jestes/howto/g++compiling.txt) for more information.

Execution
=================
To execute the program, execute these commands in the linux(yocto) command line (considering your output file is called "main.out"):

```
chmod +x main.out
./main.out
time ./main.out
```

This will output the execution time:
```
time ./main.out
```

The Code
===================
In the main you will see an example of each of the functions implemented in this library

___
> **int reset_camera()**:

> - Resets the camera
> - Sleeps por 2 seconds (specified by the manufacturer so you can get to use it)
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera was correctly reset it will return a 0 and a -1 otherwise

___
> **int enter_power_saving()**:

> - Activates the power-saving-mode
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera was correctly put in power-saving-mode it will return a 0 and a -1 otherwise

___
> **int exit_power_saving()**:

> - Deactivates the power-saving-mode
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera was correctly put out of the power-saving-mode it will return a 0 and a -1 otherwise

___
> **int change_baud(int baud)**:

> - Changes the camera's serial communication BAUD
> - The accepted BAUD Values are:
>  - 9600
>  - 19200
>  - 38400
>  - 57600
>  - 115200
> - If the BAUD chosen is not suported it will return a -1 
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera changed its BAUD successfully it will return a 0 and a -2 otherwise

___
> **int image_size(unsigned char XX)**:

> - Changes the camera's resolution
> - The accepted Resolution values and their Codes are:
>  - unsigned char **XX** = 0x00 // 640x480 
>  - unsigned char **XX** = 0x11 // 320x240
>  - unsigned char **XX** = 0x22 // 160x120
> - If the resolution chosen is not suported it will return a -1 
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera changed its resolution successfully it will return a 0 and a -1

___
> **int take_picture()**:

> - Takes a photograph 
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera took the picture it will return a 0 and a -1 otherwise

___
> **int read_size(unsigned char *XH,unsigned char *XL)**:

> - Reads the previously-taken picure's size
> - If the camera is not responding, the program will be halted waiting for the reply
> - It takes two unsigned chars by reference (this will modify their value and store there the size of the photo):
>  - **XH** corresponds to the high part of the byte of the size
>  - **XL** corresponds to the low part of the byte of the size
> - If the camera took the picture it will return a 0 and a -1 otherwise

___
> **int export_buf(unsigned char KH, unsigned char KL, unsigned char MH, unsigned char ML, unsigned char **photo_buffer, int *size)**:

> - This will export the data of the photo to a buffer sent by reference (photo_buffer)
> - If the camera is not responding, the program will be halted waiting for the reply
>  - **KH** and **KL** represent the Size of the File
>  - **MH** and **ML** represent the starting address to read from (**This value must be 0x00 and 0x00!**)
> - It returns by reference the size of the buffer (This modifies the value **size**)
> - If the camera exported the data to the buffer properly it will return a 0 and a -1 otherwise

___
> **void buf_to_pic(unsigned char **photo_buffer, int size, int num)**:

> - This will export the data of of a buffer (**photo_buffer**) to a *.jpeg* file
> - It receives the size of the buffer and an int variable called **num** which represents the output name of the **.jpeg** file
> - If the camera is not responding, the program will be halted waiting for the reply
> - It will outpout the file in the working directory

___
> **int export_pic(unsigned char KH, unsigned char KL, unsigned char MH, unsigned char ML, int i)**:

> - This will export the data of the photo to a **.jpeg** file
> - If the camera is not responding, the program will be halted waiting for the reply
>  - **KH** and **KL** represent the Size of the File 
>  - **MH** and **ML** represent the starting address to read from (**This value must be 0x00 and 0x00!**)
> - It receives an int variable called **num** which represents the output name of the **.jpeg** file
> - If the camera is not responding, the program will be halted waiting for the reply
> - It will outpout the file in the working directory
> - If the camera exported the data to the buffer properly it will return a 0 and if not it will return the number of bytes lost

___
> **int stop_cam()**:

> - This will make the camera get ready for a new picture
> - After this function is called, a new photo must be taken and there is no warranty that the last one will still be in the camera's memory
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera stopped successfully it will return a 0 and if not it will return a -1

___
> **int compression_ratio(unsigned char XX)**:

> - This function does not work properly in my camera. I am not sure if it cannot compress the ratio or my camera has some issues. Give it a try expect for the best (You should normally use a XX= 0x36)
> - If the camera is not responding, the program will be halted waiting for the reply
> - If the camera Compressed its ratio successfully it will return a 0 and a -1 otherwise


Information
===================
If you need more information about the library, read the description found in the main folder

[Back To Top](#intel-edison-linksprite-infrared-camera-library)
