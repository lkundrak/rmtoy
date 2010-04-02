struct mcb {
	short last;
	short pid;
	short len;
	/* Need to keep this last for alignment */
	char cmd[9];
};

struct mblock {
	short addr, len;
	char free;
};

int
jedna ()
{
	struct mcb mcb;
	short para;

	/* Fake first MCB from the beginning of memory */
	para = 0;
	mcb.len = firstmcb (0);
	mcb.pid = 0xffff;
	mcb.cmd[0] = '\0';
	mcb.cmd[8] = '\0';

	do {
		printf ("MCB: 0x%x: %i %x '%s'\n", para, mcb.pid, mcb.len, mcb.cmd);
		para += mcb.len;
		getmcb (para, &mcb);
	} while (!mcb.last);

	return 0x666;
}

int
bleurk ()
{
	printf ("Hello, World!\n");
	jedna ();
	return 0xbabe;
}

