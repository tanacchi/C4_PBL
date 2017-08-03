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

int main(int argc, char *argv[])
{
  int fd = -1;
  unsigned char sensor_data;
  int i, j;
  char disp[64];
  unsigned char receive_data;
  OutputInit();
  if ((fd = Serial_begin(BAUDRATE, MODEMDEVICE)) < 0) {       // 接続出来なかったらエラーを履いて終了
    sprintf(disp, "Couldn't start serial connection...\n");
    exit(-1);
  }

  /*
    表示系の初期化等
   */
  LcdInit();
  LcdRefresh();
  LcdScroll(10);
  LcdSelectFont(1);
  LcdText( 0, 2, 100, "Starting Serial Communication");

  
  /*
    センサーの初期化と設定
   */
  initSensor();
  for (i = 0; i < 4; i++) setSensorPort(i,TOUCH, 0);

  
  /*
    終了のシグナルが送られてくるまで無限ループ
   */
  while (1) {
    receive_data = Serial_read(fd);
    if (receive_data == 0xff) break; // 終了のシグナルが送られたらループを抜ける

    /*
      byteと同じ8bit変数に4つ分のセンサー情報を
      ビット演算を利用して格納
      そして送信
     */    
    sensor_data = 0;
    for (j = 0; j < 4; j++) sensor_data |= (getSensor(j) << j);
    Serial_write(fd, sensor_data);

    /*
      画面表示はテスト用のまま
      変更する時間がなかった
     */
    sprintf(disp, "%dturn %d", receive_data, i);
    LcdScroll(10);
    LcdText( 1, 2, 100, disp);
    usleep(1000);
  }

  
  /*
    ループを抜けたらセンサーを閉じて終了
   */
  LcdText( 1, 2, 100, "See ya !!!"); // 別れのあいさつ
  usleep(10000);
  closeSensor();
  return 0;
}

int Serial_begin(int brate, char* devicePath)
{
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

void Serial_end(int fd)
{
  if (fd >= 0) {
    tcsetattr(fd, TCSANOW, &oldTermio);
    close(fd);
  }
}

int Serial_write(int fd, uint8_t pbyte)
{
  ssize_t res;
  res = write(fd, &pbyte, 1);
  return (int)res;
}

uint8_t Serial_read(int fd)
{
  uint8_t c;
  read(fd, (char *)&c, 1);
  return c;
}
