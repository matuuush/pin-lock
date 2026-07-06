MCU = atmega328p
F_CPU = 16000000UL
PORT = COM3
BAUD = 115200
TARGET = PinCodeLock
BUILD_DIR = ../build
SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

CXX = avr-g++
OBJCOPY = avr-objcopy
AVRSIZE = avr-size
AVRDUDE = avrdude

CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c++11 -ffunction-sections -fdata-sections
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

all: $(HEX) size #upload

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ELF): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

size: $(ELF)
	$(AVRSIZE) -A $<

upload: $(HEX)
	$(AVRDUDE) -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i

erase_eeprom:
	$(AVRDUDE) -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U eeprom:w:0xFF:i

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all size upload clean erase_eeprom