CYGFS = C:/onHand_SDK/mec-980228/H-i386-cygwin32
RUPSDK = C:/onHand_SDK/RupSDK

TARGET = slidshow
OBJS = startup.o slidshow.o


CC = gcc
AS = as
LD = ld
RANLIB = ranlib
OBJCOPY = mn10200-elf-objcopy
SF2BIN = sf2bin


CFLAGS = -g -c -O1
CPPFLAGS = -I$(RUPSDK)/Inc
ASFLAGS = -I$(RUPSDK)/Inc
LDFLAGS = -Ttext 0x110100 -Map $(TARGET).map
LIBRUP = -L$(RUPSDK)/Lib -lrupmenu -lruptool -lrupsys -llcdbios -lpsdos -lwbios
LIBSTD = -L$(CYGFS)/mn10200-elf/lib -lm -lc
LIBGCC = -L$(CYGFS)/lib/gcc-lib/mn10200-elf/2.7-mec980228 -lgcc


$(TARGET).exf :		$(TARGET).elf
	$(OBJCOPY) -O srec $(TARGET).elf
	$(SF2BIN) $(TARGET).elf $(TARGET).exf

$(TARGET).elf :	$(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET).elf $(OBJS) $(LIBRUP) $(LIBSTD) $(LIBGCC)


startup.o: startup.s
	$(AS) $(ASFLAGS) startup.s -o startup.o

.SUFFIX: .c
.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $<
