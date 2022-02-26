CC=gcc
LD=ld
CFLAGS=-Wall -ggdb -Iinclude -ffreestanding -m32 -fno-pie
BIN=bin
SOURCES=kernel.c video.c lib.c gdt.c idt.c interrupt.c pic.c keyboard.c timer.c int.asm sound.c shapes.c piece.c board.c view.c control.c test.c
SRC_C=$(filter %.c, $(SOURCES))
SRC_ASM=$(filter %.asm, $(SOURCES))
OBJECTS=$(addprefix $(BIN)/, $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o))
EXECUTABLE=$(BIN)/tetris
VPATH=kernel:lib:video:game:keyboard:timer:boot:sound:test

$(EXECUTABLE): $(BIN)/bootsector $(BIN)/kernel
	cat $(BIN)/bootsector $(BIN)/kernel.bin /dev/zero | dd of=$(EXECUTABLE) bs=512 count=2880

$(BIN)/bootsector: bootsector.asm
	nasm -f bin $^ -o $(BIN)/bootsector

$(BIN)/kernel: $(OBJECTS)
	$(LD) -m elf_i386 -Ttext 0x1000 $^ -o $(BIN)/kernel.elf
	objcopy --only-keep-debug $(BIN)/kernel.elf $(BIN)/kernel.sym
	objcopy --strip-debug $(BIN)/kernel.elf
	objcopy -O binary $(BIN)/kernel.elf $(BIN)/kernel.bin

run:
	qemu-system-i386 -soundhw pcspk -drive format=raw,file=$(EXECUTABLE)

debug:
	qemu-system-i386 -s -S -soundhw pcspk -drive format=raw,file=$(EXECUTABLE)

-include $(BIN)/$(OBJECTS:.o=.d)

$(BIN)/%.o: %.asm
	nasm -f elf32 $< -o $(BIN)/$*.o
	nasm -M $< > $(BIN)/$*.d
	@mv -f $(BIN)/$*.d $(BIN)/$*.d.tmp
	@sed -e 's|.*:|$(BIN)/$*.o:|' < $(BIN)/$*.d.tmp > $(BIN)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BIN)/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $(BIN)/$*.d
	@rm -f $(BIN)/$*.d.tmp

$(BIN)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(BIN)/$*.o
	$(CC) -MM $(CFLAGS) $< > $(BIN)/$*.d
	@mv -f $(BIN)/$*.d $(BIN)/$*.d.tmp
	@sed -e 's|.*:|$(BIN)/$*.o:|' < $(BIN)/$*.d.tmp > $(BIN)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BIN)/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $(BIN)/$*.d
	@rm -f $(BIN)/$*.d.tmp

clean:
	rm -f $(BIN)/*.o $(BIN)/*.d $(BIN)/bootsector $(BIN)/kernel $(EXECUTABLE)
