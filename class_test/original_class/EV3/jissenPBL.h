//
//   jissenPBL.h
//   Made for LEGO Mindstorms EV3
//   Sensor Control through BricxCC
//   by Akitoshi Hanazawa April 2015
//   Kyushu Institute of Technology
//

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "lms2012\lms2012.h"

#include "C:\BricxCC\lms_api\ev3_output.h"
#include "C:\BricxCC\lms_api\ev3_command.h"
#include "C:\BricxCC\lms_api\ev3_lcd.h"

#define CH_1    0x00
#define CH_2    0x01
#define CH_3    0x02
#define CH_4    0x03

#define NXT     0
#define TOUCH   1
#define COLOR   2
#define GYRO    3
#define USONIC  4
#define HTACC 10

#define XAXIS 3
#define YAXIS 4
#define ZAXIS 5

int devTouch;
int devSense;
int devIIC;
UART *pUart;
ANALOG *pAnalog;
IIC *pIic;
IICDAT IicDat;

int mode[4];
int func[4];
unsigned char ch[]={-1, -1, -1, -1};

int accAxis = XAXIS;

int setAccAxis(int axis)
{
    accAxis = axis;

}

int getSensorGyro (unsigned char chnum) {

    int data;
    DATA8 *pData = pUart->Raw[chnum][pUart->Actual[chnum]];
    data = ((DATA16*)pData)[0];

    return data;

}

int getSensorUSonic (unsigned char chnum) {

    int data;
    DATA8 *pData = pUart->Raw[chnum][pUart->Actual[chnum]];
    data = ((DATA16*)pData)[0];

    return data;

}



int getSensorColor (unsigned char chnum) {

    int data;
    DATA8 *pData = pUart->Raw[chnum][pUart->Actual[chnum]];
    data = ((DATA8*)pData)[0];

    return data;

}



int getSensorTouch(unsigned char chnum) {

    if (pAnalog->Pin6[chnum][pAnalog->Actual[chnum]] > 500) {
        return 1;
    } else {
        return 0;
    }
}


int getSensorNXT(unsigned char chnum) {

    int data;
    data = pAnalog->Pin1[chnum][pAnalog->Actual[chnum]];

    return data;
}

int getSensorHTAcc(unsigned char chnum) {

    int data;
    data = ((int)(pIic->Raw[chnum][pIic->Actual[chnum]][accAxis]))*4;
    if (data > 0) data += (int)pIic->Raw[chnum][pIic->Actual[chnum]][accAxis-3];
    else data -= (int)pIic->Raw[chnum][pIic->Actual[chnum]][accAxis-3];
    

    return data;
}


int getSensor(int chnum) {

      int data;

      switch(func[chnum])
      {
       case NXT:
            data = getSensorNXT(chnum);
            break;
            
       case TOUCH:
            data = getSensorTouch(chnum);
            break;

       case COLOR:
            data =getSensorColor(chnum);
            break;

       case USONIC:
            data = getSensorUSonic(chnum);
            break;

       case GYRO:
            data = getSensorGyro(chnum);
            break;
            
       case HTACC:
            data = getSensorHTAcc(chnum);
            break;


       default:
            data = 0;
            break;

      }

      return data;

}



int setSensorPort(int chnum, int funcnum, int modenum)
{
    if (chnum >=0 && chnum <= 3) {
       ch[chnum] = chnum;
       func[chnum] = funcnum;
       mode[chnum] = modenum;
    }
}


int startSensor()
{
    int i, result;
    DEVCON devCon;

    for (i = 0; i < 4; i++) {
        devCon.Connection[i] = CONN_NONE;
    }

    for (i = 0; i < 4; i++) {
        if(func[i] > 1 && func[i] <10) {
              devCon.Connection[ch[i]] = CONN_INPUT_UART;
              devCon.Mode[ch[i]] = mode[i];
        }
        
        if (func[i] == 10) {
        IicDat.Port = ch[i];
	IicDat.Time = 0;
	IicDat.Repeat = 0;
	IicDat.RdLng = 6;
	IicDat.WrLng = 2;
	// Set the device I2C address
	IicDat.WrData[0] = 0x01;
	// Specify the register that will be read (0x42 = angle)
	IicDat.WrData[1] = 0x42;
	// Setup I2C comunication
	ioctl(devIIC,IIC_SETUP,&IicDat);
        }
        
    }

    result = ioctl(devSense, UART_SET_CONN, &devCon);

    return result;

}


void initSensor()
{
    int i;

    devSense = open("/dev/lms_uart", O_RDWR | O_SYNC);

    if (devSense < 0) {
       LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Open devSense");
       Wait(1000);
       exit(1);
    }

    pUart = (UART *)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, devSense, 0);

    if (pUart == MAP_FAILED) {
       LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Map Device");
       Wait(1000);
       exit(1);
    }
    
    

    devTouch = open("/dev/lms_analog", O_RDWR | O_SYNC);

    if (devTouch < 0) {
       LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Open devTouch");
       Wait(1000);
       exit(1);
    }

    pAnalog = (ANALOG *) mmap(0, sizeof(ANALOG), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, devTouch, 0);

    if (pAnalog == MAP_FAILED) {
       LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Map devAnalog");
       Wait(1000);
       exit(1);
    }
    
    if((devIIC = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC)) == -1)
	  {
       LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Open devIIC");
       Wait(1000);
       exit(1);
    }
    
    pIic  =  (IIC*)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, devIIC, 0);
    if (pIic == MAP_FAILED)
    {
		   LcdScroll(20);
       LcdText( 0, 2, 100, "Failed Map devIIC");
       Wait(1000);
       exit(1);
	  }
	  


    return;
}


void closeSensor()
{
    munmap(pUart, sizeof(UART));
    close(devSense);

    munmap(pAnalog, sizeof(ANALOG));
    close(devTouch);

     munmap(pIic, sizeof(UART));
    close(devIIC);
}

