#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include "lms2012\lms2012.h"
#include "C:\BricxCC\lms_api\ev3_output.h"
#include "C:\BricxCC\lms_api\ev3_command.h"
#include "C:\BricxCC\lms_api\ev3_lcd.h"
#include "jissenPBL.h"

#define BAUDRATE 9600
#define MODEMDEVICE "/dev/ttyACM0"

struct termios oldTermio;

int Serial_begin(int brate, char* devicePath);
void Serial_end(int fd);
int Serial_write(int fd, uint8_t pbyte);
uint8_t Serial_read(int fd);
int analogToCentimeter(int analogValue);

int main(int argc, char *argv[]) {
  int fd = -1;
  unsigned char sensor_data;
  int i, j;
  char disp[64];
  unsigned char receive_data;
  OutputInit();
  if ((fd = Serial_begin(BAUDRATE, MODEMDEVICE)) < 0) {
    sprintf(disp, "Waiting for serial connection...\n");
    usleep(500000);
    exit -1;
  }
  LcdInit();
  LcdRefresh();
  LcdScroll(10);
  LcdSelectFont(1);
  LcdText( 0, 2, 100, "Start Serial Communication");

  initSensor();
  for (i = 0; i < 4; i++) setSensorPort(i,TOUCH, 0);

  for (i = 0; i < 50000; i++) {
    receive_data = Serial_read(fd);
    if (receive_data == 0xff) {
    sprintf(disp, "See ya !!!!\n");
    break;
    }
    sensor_data = 0;
    for (j = 0; j < 4; j++) sensor_data |= (getSensor(j) << j);
    Serial_write(fd, sensor_data);
    sprintf(disp, "%dturn %d", receive_data, i);
    LcdScroll(10);
    LcdText( 1, 2, 100, disp);
    usleep(1000);
  }
  LcdScroll(10);
  LcdText( 1, 2, 100, disp);
  usleep(10000);
  closeSensor();
  return 0;
}

int Serial_begin(int brate, char* devicePath) {
  int fd;
  struct termios newTermio;
  fd = open(devicePath, O_RDWR | O_NOCTTY);
  if (fd < 0) {
    perror(devicePath);
    exit(-1);
  }
  tcgetattr(fd, &oldTermio);
  newTermio.c_iflag = 0;
  newTermio.c_oflag = 0;
  newTermio.c_cflag = 0;
  newTermio.c_lflag = 0;
  newTermio.c_line = 0;
  memset(newTermio.c_cc, '\0', sizeof(newTermio.c_cc));
  switch (brate) {
  case 300:
    newTermio.c_cflag = B300 | CS8 | CLOCAL | CREAD;
    break;
  case 1200:
    newTermio.c_cflag = B1200 | CS8 | CLOCAL | CREAD;
    break;
  case 2400:
    newTermio.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
    break;
  case 4800:
    newTermio.c_cflag = B4800 | CS8 | CLOCAL | CREAD;
    break;
  case 9600:
    newTermio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    break;
  case 19200:
    newTermio.c_cflag = B19200 | CS8 | CLOCAL | CREAD;
    break;
  case 38400:
    newTermio.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
    break;
  case 57600:
    newTermio.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
    break;
  case 115200:
    newTermio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    break;
  default:
    newTermio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    break;
  }
  newTermio.c_iflag = IGNPAR;
  newTermio.c_oflag = 0;
  newTermio.c_lflag = 0;
  newTermio.c_cc[VTIME] = 0;
  newTermio.c_cc[VMIN] = 1;
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newTermio);
  sleep(3);
  return (fd);
}

void Serial_end(int fd) {
  if (fd >= 0) {
    tcsetattr(fd, TCSANOW, &oldTermio);
    close(fd);
  }
}

int Serial_write(int fd, uint8_t pbyte) {
  ssize_t res;
  res = write(fd, &pbyte, 1);
  return (int)res;
}

uint8_t Serial_read(int fd) {
  uint8_t c;
  read(fd, (char *)&c, 1);
  return c;
}
