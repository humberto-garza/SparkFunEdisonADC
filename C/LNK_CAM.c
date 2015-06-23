#include "LNK_CAM.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int reset_camera()
{
	int result =-1;
	char buf[4];
	unsigned char reset[4] = {0x56, 0x00, 0x26, 0x00}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c",reset[0],reset[1],reset[2],reset[3]);
	fgets(buf,4,camera);

	//printf("%x_%x_%x_%x\n",buf[0],buf[1],buf[2],buf[3]);
	if(buf[0]==0x76 && buf[2]==0x26)
		result =0;
	fclose(camera);
	sleep(2);
	system("stty -F /dev/ttyMFD1 38400");
	return result;
}

int take_picture()
{
	int result =-1;
	char buf[4];
	unsigned char take[5] = {0x56, 0x00, 0x36, 0x01, 0x00}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c",take[0],take[1],take[2],take[3],take[4]);
	fgets(buf,4,camera);
	//printf("%x_%x_%x_%x\n",buf[0],buf[1],buf[2],buf[3]);
	if(buf[0]==0x76 && buf[2]==0x36)
		result =0;

	fclose(camera);
	return result;
}

int read_size(unsigned char *XH,unsigned char *XL)
{
	int result =-1;
	unsigned char buf[10];
	unsigned char size[5] = {0x56, 0x00, 0x34, 0x01, 0x00}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c",size[0],size[1],size[2],size[3],size[4]);

	fgets(buf,10,camera);
	//printf("%02x_%02x_%02x_%02x_%02x_%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9]);
	if(buf[0]==0x76 && buf[2]==0x34)
		result =0;

	*XH = buf[7];
	*XL = buf[8];
	fclose(camera);

	return result;
}

int export_buf(unsigned char KH, unsigned char KL, unsigned char MH, unsigned char ML, unsigned char **photo_buffer, int *size)
{
	//Open Camera Linux File
	int camera = open("/dev/ttyMFD1", O_RDWR | O_NOCTTY);
	if (camera == -1)
		return -1;

	//Time to send file delimiters
	unsigned char XH = 0x00;
	unsigned char XL = 0x00;

	//Command to Open Camera File
	unsigned char jpeg[16] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, MH, ML, 0x00, 0x00, KH, KL, XH, XL}; 
	//Send command to return the JPEG File by the camera
	int n = write(camera, jpeg, 16);

	//Assign the Size of the JPEG (It mus be calculated in these steps in order to make it work)
	int fsizeH = ((long)KH)<<8;
	int fsizeL = ((long)KL);
	fsizeH += fsizeL +10 ;

	//Allocate the Temporal Extra Space for the buffer
	*photo_buffer = malloc(fsizeH);
	*size = fsizeH;

	int total = fsizeH/2048;
	int x, aloc=0;

	for(x=0; x<total+1; x++)
	{	
		n = read(camera, *photo_buffer+aloc, 2048);
		aloc += n;
	}

	close(camera);
	return (aloc- *size);
}

int export_pic(unsigned char KH, unsigned char KL, unsigned char MH, unsigned char ML, int i)
{
	//Open Camera Linux File
	int camera = open("/dev/ttyMFD1", O_RDWR | O_NOCTTY);
	if (camera == -1)
		return -1;

	//Time to send file delimiters
	unsigned char XH = 0x00;
	unsigned char XL = 0x00;

	//Command to Open Camera File
	unsigned char jpeg[16] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, MH, ML, 0x00, 0x00, KH, KL, XH, XL}; 
	//Send command to return the JPEG File by the camera
	int n = write(camera, jpeg, 16);

	//Assign the Size of the JPEG (It mus be calculated in these steps in order to make it work)
	int fsizeH = ((long)KH)<<8;
	int fsizeL = ((long)KL);
	fsizeH += fsizeL +10 ;

	//Allocate the Temporal Extra Space for the buffer
	unsigned char *photo_buffer = malloc(fsizeH);

	int total = fsizeH/2048;
	int x, aloc=0;

	for(x=0; x<total+1; x++)
	{	
		n = read(camera, photo_buffer+aloc, 2048);
		aloc += n;
	}
	//Open JPEG File to Export the Photo
	char buffer[32]={0x00};
	snprintf(buffer, sizeof(buffer),"foto%d.jpg",i);
	FILE *foto = fopen(buffer, "w");

	int m;
	for(m = 5; m<fsizeH-5; m++)
		fputc(photo_buffer[m], foto);


	fclose(foto);
	close(camera);
	return (aloc- fsizeH);
}



void buf_to_pic(unsigned char **photo_buffer, int size, int num)
{
	//Open JPEG File to Export the Photo
	char buffer[32]={0x00};
	snprintf(buffer, sizeof(buffer),"foto%d.jpg", num);
	FILE *foto = fopen(buffer, "w");

	int x;
	for(x=5; x<size-5; x++)
		fputc((*photo_buffer)[x],foto);

	fclose(foto);
}

int stop_cam()
{
	int result =-1;
	char buf[4];
	unsigned char stop[5] = {0x56, 0x00, 0x36, 0x01, 0x03}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c",stop[0],stop[1],stop[2],stop[3],stop[4]);
	
	fgets(buf,4,camera);
	//printf("%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3]);
	if(buf[0]==0x76 && buf[2]==0x36)
		result =0;

	fclose(camera);
	return result;
}

int compression_ratio(unsigned char XX)
{
	int result =-1;
	unsigned char buf[6];
	unsigned char ratio[9] = {0x56, 0x00, 0x31, 0x05 , 0x01, 0x01, 0x12, 0x04, XX}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c%c%c%c%c",ratio[0],ratio[1],ratio[2],ratio[3],ratio[4],ratio[5],ratio[6],ratio[7],ratio[8]);
	fgets(buf,6,camera);

	//printf("%02x_%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
	if(buf[0]==0x76 && buf[2]==0x31 && buf[5]==XX)
		result =0;

	fclose(camera);
	return result;
}	

int image_size(unsigned char XX)
{
	int result =-1;
	unsigned char buf[5];
	unsigned char ratio[9] = {0x56, 0x00, 0x31, 0x05 , 0x04, 0x01, 0x00, 0x19, XX}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c%c%c%c%c",ratio[0],ratio[1],ratio[2],ratio[3],ratio[4],ratio[5],ratio[6],ratio[7],ratio[8]);
	fgets(buf,5,camera);

	//printf("%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
	if(buf[0]==0x76 && buf[2]==0x31)
		result =0;
	
	fclose(camera);
	result = result + reset_camera();
	return result;
}	

int change_baud(int baud)
{
	int result =-1;
	//Default Baud = 38400
	unsigned char BH = 0x2a; 
	unsigned char BL = 0xf2;
	switch(baud)
	{
		///////////////////////////
		case 9600:
			//printf("BAUD: %d\n",9600);
			BH = 0xae; 
			BL = 0xc8;
			break;
		///////////////////////////
		case 19200:
			//printf("BAUD: %d\n",19200);
			BH = 0x56; 
			BL = 0xe4;
			break;
		///////////////////////////
		case 38400:
			//printf("BAUD: %d\n",38400);
			BH = 0x2a; 
			BL = 0xf2;
			break;
		///////////////////////////
		case 57600:
			//printf("BAUD: %d\n",57600);
			BH = 0x1c; 
			BL = 0x4c;
			break;;
		///////////////////////////
		case 115200:
			//printf("BAUD: %d\n",115200);
			BH = 0x0d; 
			BL = 0xa6;
			break;
		///////////////////////////
		default:
			//printf("DEFAULT-38400-\n");
			return result;
			break;
		///////////////////////////
	}
	result = -2;
	unsigned char buf[6];
	unsigned char baudarr[7] = {0x56, 0x00, 0x24, 0x03 , 0x01, BH, BL}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c%c%c",baudarr[0],baudarr[1],baudarr[2],baudarr[3],baudarr[4],baudarr[5],baudarr[6]);
	fgets(buf,5,camera);
	//printf("%02x_%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
	if(buf[0]==0x76 && buf[2]==0x24)
		result =0;


	char buffer[32]={0x00};
	snprintf(buffer, sizeof(buffer),"stty -F /dev/ttyMFD1 %d", baud);
	system(buffer);



	fclose(camera);
	return result;	
}

int enter_power_saving()
{
	int result =-1;
	unsigned char buf[5];
	unsigned char enter[7] = {0x56, 0x00, 0x3E, 0x03 , 0x00, 0x01, 0x01}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c%c%c",enter[0],enter[1],enter[2],enter[3],enter[4],enter[5],enter[6]);
	fgets(buf,5,camera);

	//printf("%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
	if(buf[0]==0x76 && buf[2]==0x3E)
		result =0;
	
	fclose(camera);
	return result;
}	

int exit_power_saving()
{
	int result =-1;
	unsigned char buf[5];
	unsigned char exitp[7] = {0x56, 0x00, 0x3E, 0x03 , 0x00, 0x01, 0x00}; 
	FILE *camera = fopen("/dev/ttyMFD1", "a+");

	fprintf(camera,"%c%c%c%c%c%c%c",exitp[0],exitp[1],exitp[2],exitp[3],exitp[4],exitp[5],exitp[6]);
	fgets(buf,5,camera);

	//printf("%02x_%02x_%02x_%02x_%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
	if(buf[0]==0x76 && buf[2]==0x3E)
		result =0;
	
	fclose(camera);
	return result;
}	