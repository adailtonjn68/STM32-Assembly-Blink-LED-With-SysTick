PROJECT_NAME:=blink_led_with_systick
TOOLCHAIN:=arm-none-eabi

CPU:=cortex-m3
LINKER:=STM32F103C8TX_FLASH.ld

WARNINGS:=-Wall
SYNTAX:=-masm-syntax-unified
CFLAGS:=-x assembler -c -mcpu=$(CPU) $(SYNTAX) -mfloat-abi=soft -mthumb $(WARNINGS) -g3 -O0
LINK_FLAGS:=-mcpu=$(CPU) $(SYNTAX) -mfloat-abi=soft -mthumb --specs=nosys.specs -nostdlib -Wl,-Map=./Debug/$(PROJECT_NAME).map -T$(LINKER) -g3
INC_DIR:=./Core/Inc \
         ./Core/Startup
INCLUDES:=$(addprefix -I,$(INC_DIR))

all: compile


debug: compile
	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg &
	@#OPENOCD_PID=$!
	gdb-multiarch ./Debug/$(PROJECT_NAME).elf -ex "target remote localhost:3333"; echo ' '
	@#kill $(ps axf | grep '[o]penocd' | awk '{print $1}')
	killall openocd
	@#kill $OPENOCD_PID
	@#echo $OPENOCD_PID


compile: Debug/$(PROJECT_NAME).bin

Debug/$(PROJECT_NAME).bin: Debug/$(PROJECT_NAME).elf
	$(TOOLCHAIN)-objcopy -O binary ./Debug/$(PROJECT_NAME).elf ./Debug/$(PROJECT_NAME).bin
	@echo 'Finished building target: $(PROJECT_NAME).bin'
	@echo ' '
	$(TOOLCHAIN)-objdump -D -bbinary -marm ./Debug/$(PROJECT_NAME).bin -Mforce-thumb > ./Debug/$(PROJECT_NAME).list
	@echo ' '

Debug/$(PROJECT_NAME).elf: Debug/Core/Src/main.o Debug/Core/Startup/startup_stm32f103c8t6.o Debug/Core/Src/systick_config.o Debug/Core/Src/stm32f10x.o
	$(TOOLCHAIN)-gcc ./Debug/Core/Src/main.o ./Debug/Core/Startup/startup_stm32f103c8t6.o ./Debug/Core/Src/systick_config.o Debug/Core/Src/stm32f10x.o -Wall $(LINK_FLAGS) -o ./Debug/$(PROJECT_NAME).elf
	@echo 'Finished building target: $(PROJECT_NAME).elf'
	@echo ' '	

Debug/Core/Src/main.o: Core/Src/main.s Core/Inc/stm32f10x.inc
	$(TOOLCHAIN)-gcc $(CFLAGS) -I./Core/Inc ./Core/Src/main.s -o ./Debug/Core/Src/main.o

Debug/Core/Startup/startup_stm32f103c8t6.o: Core/Startup/startup_stm32f103c8t6.s
	$(TOOLCHAIN)-gcc $(CFLAGS) ./Core/Startup/startup_stm32f103c8t6.s -o ./Debug/Core/Startup/startup_stm32f103c8t6.o

Debug/Core/Src/systick_config.o: Core/Src/systick_config.s Core/Inc/stm32f10x.inc
	$(TOOLCHAIN)-gcc $(CFLAGS) -I./Core/Inc ./Core/Src/systick_config.s -o ./Debug/Core/Src/systick_config.o

Debug/Core/Src/stm32f10x.o: Core/Src/stm32f10x.s Core/Inc/stm32f10x.inc
	$(TOOLCHAIN)-gcc $(CFLAGS) -I./Core/Inc ./Core/Src/stm32f10x.s -o ./Debug/Core/Src/stm32f10x.o


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
	rm -f Debug/*.bin Debug/*.elf Debug/*.o Debug/*.map

.PHONY: clean all
