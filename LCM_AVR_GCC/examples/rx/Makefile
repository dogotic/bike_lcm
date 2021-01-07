TARGET=RX

SRC=main.c 
SRC+=../../src/UART/uart.c
SRC+=../../src/NRF24L01/nrf24l01.c

OBJ+=main.o
OBJ+=nrf24l01.o
OBJ+=uart.o

INC+=-I../../src/UART/
INC+=-I../../src/NRF24L01/

MCU=atmega328p
AVRDUDE_MCU=atmega328p
AVRDUDE_PROGRAMMER=arduino
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt
MATH_LIB = -lm

CFLAGS=-Wall -Os -mmcu=$(MCU) -DUSE_LOGGING=1 -DF_CPU=8000000UL -std=gnu99
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += $(PRINTF_LIB_FLOAT) $(MATH_LIB)
AVRDUDE_FLAGS= -p$(AVRDUDE_MCU) -c $(AVRDUDE_PROGRAMMER) -P COM3 -b 57600

hex:
	avr-gcc -g -Os -mmcu=$(MCU) -c $(INC) $(SRC) $(INC) $(CFLAGS)
	avr-gcc -g -mmcu=$(MCU) $(LDFLAGS) -o $(TARGET).elf $(OBJ) 
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size -C --mcu=${MCU} ${TARGET}.elf

clean:
	rm -rf *.o *.elf *.hex $(TARGET).map

program_flash:
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$(TARGET).hex:i
#	putty -load AVR
