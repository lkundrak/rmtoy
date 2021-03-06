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
	printf ("\n----\n");
	nicstart ();
	return 0xbabe;
}

/* Compiler invokes call to this, when passing structure as an argument.
 * We should never do that. A structure passed is a structure abused.
void *
memcpy (dest, src, len)
	void *dest, *src;
	int len;
{
	void *ret = dest;
	panic ("Memcpy");
	while (len--)
		*(char *)dest++ = *(char *)src++;
	return ret;
}
*/
