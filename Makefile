ASSEMBLY_OBJS = $(addsuffix .o,$(basename $(wildcard *.S)))
C_OBJS = $(addsuffix .o,$(basename $(wildcard *.c)))
CPP_OBJS = $(addsuffix .o,$(basename $(wildcard *.cpp)))
GCC_WARNS  = -Werror -Wall -Wextra -Wshadow -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings
GCC_WARNS += -Wredundant-decls -Wstrict-prototypes -Wmissing-prototypes -pedantic # -Wconversion
INCLUDE_OPT = -I./
TOOLCHAIN_PREFIX = riscv32-unknown-elf-

input.bin: input.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< $@
	$(TOOLCHAIN_PREFIX)objdump -d $<
	chmod -x $@

input.elf: $(ASSEMBLY_OBJS) $(C_OBJS) $(CPP_OBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc -Os -march=rv32im -ffreestanding -nostdlib -o $@ \
		-Wl,-Bstatic,-T,sections.lds,-Map,input.map,--strip-debug \
		$(ASSEMBLY_OBJS) $(C_OBJS) $(CPP_OBJS) -lgcc
	chmod -x $@

%.o: %.cpp
	$(TOOLCHAIN_PREFIX)g++ -c -march=rv32im -o $@ $(INCLUDE_OPT) $<

%.o: %.c
	$(TOOLCHAIN_PREFIX)gcc -c -march=rv32im -o $@ $(INCLUDE_OPT) $<
	
%.o: %.S
	$(TOOLCHAIN_PREFIX)gcc -c -march=rv32im -o $@ $(INCLUDE_OPT) $<

clean:
	rm -vrf *.elf *.bin *.o *.map 

.PHONY: input.bin
