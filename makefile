PROJECT_NAME:=blink_led
TOOLCHAIN:=arm-none-eabi

CPU:=cortex-m3
LINKER:=STM32F103C8TX_FLASH.ld

WARNINGS:=-Wall
SYNTAX:=-masm-syntax-unified
CFLAGS:=-x assembler -c -mcpu=$(CPU) $(SYNTAX) -mfloat-abi=soft -mthumb $(WARNINGS) -g3 -O0
INC_DIR:=./Core/Inc \
         ./Core/Startup
INCLUDES:=$(addprefix -I,$(INC_DIR))

all: compile


debug:
	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg &
	@#OPENOCD_PID=$!
	gdb-multiarch ./Debug/$(PROJECT_NAME).elf -ex "target remote localhost:3333"; echo ' '
	@#kill $(ps axf | grep '[o]penocd' | awk '{print $1}')
	killall openocd
	@#kill $OPENOCD_PID
	@#echo $OPENOCD_PID

compile:
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLUDES) ./Core/Src/main.s -o ./Debug/Core/Src/main.o
	$(TOOLCHAIN)-gcc ./Debug/Core/Src/main.o -Wall --specs=nosys.specs -nostdlib -T$(LINKER) -o ./Debug/$(PROJECT_NAME).elf
	@echo 'Finished building target: $(PROJECT_NAME).elf'
	@echo ' '
	$(TOOLCHAIN)-objcopy -O binary ./Debug/$(PROJECT_NAME).elf ./Debug/$(PROJECT_NAME).bin
	@echo 'Finished building target: $(PROJECT_NAME).bin'
	@echo ' '
	$(TOOLCHAIN)-objdump -D -bbinary -marm ./Debug/$(PROJECT_NAME).bin -Mforce-thumb > ./Debug/$(PROJECT_NAME).list
	@echo ' '

flash:
	st-flash write ./Debug/$(PROJECT_NAME).bin 0x8000000

requisites:
	sudo apt install gcc-arm-none-eabi
	sudo apt install stlink-tools
	sudo apt install openocd
	sudo apt install gdb-multiarch

clean:
	rm -f Debug/Core/Src/*.o
	rm -f Debug/Core/Startup/*.o
	rm -f Debug/*.bin Debug/*.elf Debug/*.o
	rm -f Debug/$(PROJECT_NAME)
	rm -f Debug/$(PROJECT_NAME).list

.PHONY: clean all
