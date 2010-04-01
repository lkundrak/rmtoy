int
jedna ()
{
	void *mcb;
	char cmd[9];
	cmd[8] = '\0';

	printf ("Hello, World!\n");
	for (mcb = nextmcb (0); mcb; mcb = nextmcb (mcb)) {
		mcbname (mcb, cmd);
		printf ("MCB: 0x%x: '%s'\n", mcb, cmd);
	}

	return 0x666;
}

int
bleurk ()
{
	jedna ();
	return 0xbabe;
}

