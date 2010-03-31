void panic (wtf);

/* Has to be first */

void
main ()
{
	bleurk ();
	panic ("No kruwa japierdole");
	while (1);
}

void
panic (wtf)
	char *wtf;
{
	printf ("PANIC: %s\n", wtf);
	exit ();
}
