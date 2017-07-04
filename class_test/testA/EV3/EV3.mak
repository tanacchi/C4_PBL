PROGRAM=EV3
DOBJECTS=C:\BricxCC\lms_api\ev3_button.o C:\BricxCC\lms_api\ev3_command.o C:\BricxCC\lms_api\ev3_lcd.o C:\BricxCC\lms_api\ev3_output.o C:\BricxCC\lms_api\ev3_sound.o C:\BricxCC\lms_api\ev3_timer.o 
TOOLPREFIX=arm-none-linux-gnueabi-

all:: realclean $(DOBJECTS) $(PROGRAM)

download:: all

#pscp -scp -pw "" EV3 root@192.168.2.128:/media/card

clean::
	rm -f *.o *.ppu *.rst

realclean:: clean
	rm -f $(PROGRAM)

FLAGS=
LDFLAGS=-Wl,-R/media/card/lib

CC=$(TOOLPREFIX)gcc

# how to link executable
EV3: EV3.c
	$(CC) $(FLAGS) $(LDFLAGS) $< -o$@ C:\BricxCC\lms_api\ev3_button.o C:\BricxCC\lms_api\ev3_command.o C:\BricxCC\lms_api\ev3_lcd.o C:\BricxCC\lms_api\ev3_output.o C:\BricxCC\lms_api\ev3_sound.o C:\BricxCC\lms_api\ev3_timer.o 

# how to compile source
%.o: %.c
	$(CC) $(FLAGS) -c $< -o$@

