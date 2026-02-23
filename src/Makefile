MCU = atmega328p
F_CPU = 16000000UL
PORT = COM3
BAUD = 115200
TARGET = PinCodeLock
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

CXX = avr-g++
OBJCOPY = avr-objcopy
AVRSIZE = avr-size
AVRDUDE = avrdude

CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c++11 -ffunction-sections -fdata-sections
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

all: $(TARGET).hex size upload

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

size: $(TARGET).elf
	$(AVR-SIZE) -A $<

upload: $(TARGET).hex
	$(AVRDUDE) -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i

clean:
	rm -f *.o *.elf *.hex

.PHONY: all size upload clean