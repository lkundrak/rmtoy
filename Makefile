#bcc -0 -Md -Ms -S hello.c
#as86 -0 -b bin -o lala.out -s sym.tab hello.s
#objdump -m i8086 -b binary -M i8086 -D --adjust-vma=0x100 bin

# Dev86 setup
CC = bcc
CFLAGS = -0 -Md -Ms
#-A-O
LD = ld86
LDFLAGS = -0 -d -M -T0x100 -t -m
AS = as86
ASFLAGS = -0 -g
START = main.o
EXT = .com
CPPFLAGS = -DDEBUG

# For debug assemply dumps
.SUFFIXES: .c .s
%.s: %.c
	$(CC) $(CFLAGS) -o $@ -S $<

# start.o needs to be first
OBJECTS = $(START) lo.o bus.o prf.o lib.o nic.o

hello$(EXT): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

nic.o: nic.h

dump: dump$(EXT)
dump.com: hello$(EXT)
	objdump -m i8086 -b binary -M i8086 -D --adjust-vma=0x100 $<
	(dd if=/dev/zero bs=256 count=1 2>/dev/null; cat $<) |hexdump -C
	size86 $(OBJECTS)

clean:
	rm -f $(OBJECTS) hello$(EXT)

# Testin'
VIRT = qemu
FLOPPY = floppy.img
run: run.$(VIRT)

$(FLOPPY):
	mformat -i $(FLOPPY) -C -f 1440 ::
mkfloppy: hello$(EXT) $(FLOPPY)
	-mdel -i $(FLOPPY) ::/$<
	mcopy -i $(FLOPPY) $< ::

run.vbox: mkfloppy
	VBoxSDL --startvm 2bf639ed-eb6b-4519-9103-7e1da010f02b --hda msdos.vmdk --fda $(FLOPPY)

run.qemu: mkfloppy
	qemu -M isapc -net nic,model=ne2k_isa -fda $(FLOPPY)

run.dosbox: hello$(EXT)
	dosbox $<
