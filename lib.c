struct mcb {
	short last;
	short pid;
	short len;
	/* Need to keep this last for alignment */
	char cmd[9];
};

int
jedna ()
{
	struct mcb mcb;
	short para;
	mcb.cmd[8] = '\0';

	printf ("Hello, World!\n");
	for (para = firstmcb (0); !mcb.last; para += mcb.len + 1) {
		getmcb (para, &mcb);
		printf ("MCB: 0x%x: %i %x '%s'\n", para, mcb.pid, mcb.len, mcb.cmd);
	}

	return 0x666;
}

int
bleurk ()
{
	jedna ();
	return 0xbabe;
}

