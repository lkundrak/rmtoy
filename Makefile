# Dev86 setup
CC = bcc
CFLAGS = -0 -Md -Ms -W
#-A-O
LD = ld86
LDFLAGS = -0 -d -T0x100
#verbose #LDFLAGS = -0 -d -M -T0x100 -t -m
AS = as86
ASFLAGS = -0 -g -W
EXT = .com
CPPFLAGS = -DDEBUG

# All targets
ALL = dumpvga$(EXT) hello$(EXT) trolol$(EXT)

# Single target, for debug runs
RUN = hello$(EXT)

# Library
OBJECTS = lo.o dos.o bios.o bus.o prf.o

all: $(ALL)

dumpvga.com: vga.o
trolol.com: lib.o nic.o

# For debug assemply dumps
.SUFFIXES: .c .s
%.s: %.c
	$(CC) $(CFLAGS) -o $@ -S $<

# Link executables
.SUFFIXES: $(EXT) .o
%$(EXT): %.o $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

dump: dump$(EXT)
dump.com: $(RUN) $(OBJECTS)
	objdump -m i8086 -b binary -M i8086 -D --adjust-vma=0x100 $<
	(dd if=/dev/zero bs=256 count=1 2>/dev/null; cat $<) |hexdump -C
	size86 $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(ALL)

# Testin'
VIRT = dosbox
FLOPPY = floppy.img
run: run.$(VIRT)

$(FLOPPY):
	mformat -i $(FLOPPY) -C -f 1440 ::
mkfloppy: $(RUN) $(FLOPPY)
	-mdel -i $(FLOPPY) ::/$<
	mcopy -i $(FLOPPY) $< ::

run.vbox: mkfloppy
	VBoxSDL --startvm 2bf639ed-eb6b-4519-9103-7e1da010f02b --hda msdos.vmdk --fda $(FLOPPY)

run.qemu: mkfloppy
	qemu -M isapc -net nic,model=ne2k_isa -fda $(FLOPPY)

run.dosbox: $(RUN)
	dosbox $<
