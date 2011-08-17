#define NULL ((void *)0)

struct reg {
	/* Addresses */
	signed read;
	signed write;
	char *desc;
};

/* Indirectly indexed registers */
struct indreg {
	struct reg *address, *data, *reset;
	char size;
	struct *desc;
};

struct reg regs[] = {
	/* 00 */ { 0x3c0, 0x3c0, "Attribute Controller Address" },
	/* 01 */ { 0x3c1,    -1, "Attribute Controller Data" },
	/* 02 */ { 0x3c2,    -1, "Input Status #0 Register" },
	/* 03 */ { 0x3c4, 0x3c4, "Sequencer Register Address" },
	/* 04 */ { 0x3c5, 0x3c5, "Sequencer Register Data" },
	/* 05 */ { 0x3ca, 0x3da, "Feature Control Register" },
	/* 06 */ { 0x3cc, 0x3c2, "Miscellaneous Output Register" },
	/* 07 */ { 0x3ce, 0x3ce, "Graphics Controller Register Address" },
	/* 08 */ { 0x3cf, 0x3cf, "Graphics Controller Register Data" },
	/* 09 */ { 0x3d4, 0x3d4, "CRT Controller Register Address" },
	/* 10 */ { 0x3d5, 0x3d5, "CRT Controller Register Data" },
	/* 11 */ { 0x3da,    -1, "Input Status #1 Register" },
	/* 12 */ { -1, -1, NULL }
};

struct indreg indregs[] = {
	{ &regs[0], &regs[1], &regs[11], 0x15, "Attribute Controller Registers" },
	{ &regs[3], &regs[4], NULL, 0x05, "Sequencer Registers" },
	{ &regs[7], &regs[8], NULL, 0x09, "Graphics Controller Registers" },
	{ &regs[9], &regs[10], NULL, 0x19, "CRT Controller Registers" },
	{ NULL, NULL, NULL, -1, NULL }
};

void
dumpvga ()
{
	static signed char vga = 0x00;
	char reg;

	/* Directly addressed */
	for (reg = 0; regs[reg].desc; reg++) {
		register value;

		/* Deal with MDA-compatible addressing modes */
		if (regs[reg].read >= 0x3d0 && regs[reg].read < 0x3e0) {
			regs[reg].read += vga;
		}
		if (regs[reg].write >= 0x3d0 && regs[reg].write < 0x3e0) {
			regs[reg].write += vga;
		}

		/* Actual read */
		value = inb (regs[reg].read);

		/* Calculate the MDA-compatible adjustment */
		if (reg == 0 && value & 0x1 == 0x0) {
			vga = -0x20;
		}
		printf ("%s: 0x%x\n", regs[reg].desc, value);
	}

	/* Indirectly addressed */
	for (reg = 0; indregs[reg].address; reg++) {
		char index;

		printf ("\n%s:\n", indregs[reg].desc);
		for (index = 0; index < indregs[reg].size; index++) {
			if (indregs[reg].reset)
				inb (indregs[reg].reset->read);
			outb (indregs[reg].address->write, index);
			printf ("0x%x ", inb (indregs[reg].data->read));
		}
		printf ("\n");
	}
}
