#define BASE	0x300
#define IRQ	9

#include "nic.h"

void
nicaddr ()
{
	int i;
	char eth_id[6];

	outb (BASE + CR, STP | PAGE0);

	/* Byte count = 6 */
	outb (BASE + RBCR0, 0x06);
	outb (BASE + RBCR1, 0x00);

	/* Start address = 0 */
	outb (BASE + RSAR0, 0x00);
	outb (BASE + RSAR1, 0x00);

	/* DMA */
	outb (BASE + CR, STP | READ);

	/* Read the station ID from EPROM */
	printf ("nic: Ethernet ID: ");
	for (i = 0; i < 6; i++) {
		/* WTF is 0x10? */
		printf ("%x%c", eth_id[i] = inb (BASE + 0x10),
			i < 5 ? ':' : '\r');
	}
	putchar ('\n');

	/* Set the station ID on the controller */
	outb (BASE + CR, STP | PAGE2);
	for (i = 0; i < 6; i++)
		outb (BASE + PAR0 + i, eth_id[i]);
}

void
nicinit ()
{
	outb (BASE + CR, STP | PAGE0);
	outb (BASE + DCR, WTS | LS | AR | B8);

	/* Byte count = 0 */
	outb (BASE + RBCR0, 0x00);
	outb (BASE + RBCR1, 0x00);

	/* Accept all valid packets on the wire */
	outb (BASE + RSR, PRO | AR | AB | AM);

	/* Configure the ring WTF */
	outb (BASE + TCR, MODE1);
	outb (BASE + TPSR, 0x20);
	outb (BASE + PSTART, 0x26);
	outb (BASE + BNRY, 0x40);
	outb (BASE + PSTOP, 0x40);

	outb (BASE + CR, STP | PAGE1);
	outb (BASE + CURR, 0x26); /* WTF */
	outb (BASE + CR, STP | PAGE0);

	/* Interrupt on most occassions */ /* WTF receiving an int here */
	outb (BASE + IMR, PRXE | PTXE | RXEE | TXEE | OVWE | CNTE | RDCE);
	outb (BASE + TCR, MODE0);
}

void
nicintr ()
{

	outb (BASE + CR, STP | PAGE0);

	printf ("nic: IRQ. ISR: 0x%x, RSR: 0x%x, BNRY: 0x%x, ",
		inb (BASE + ISR),
		inb (BASE + RSR),
		inb (BASE + BNRY)
	);

	outb (BASE + CR, STP | PAGE1);
	printf ("CURR: 0x%x\n", inb (BASE + CURR));
	outb (BASE + CR, STP | PAGE0);

	/* Restore interrupts */
	outb (BASE + IMR, PRXE | PTXE | RXEE | TXEE | OVWE | CNTE | RDCE);
}

void
nicstart ()
{
/*
	register_irq (IRQ, nicintr);
*/
	nicinit ();
	nicaddr ();
}

