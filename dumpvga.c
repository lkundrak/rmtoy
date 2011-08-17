/* Has to be first */

void
main ()
{
	vgamode (0x13);
	dumpvga ();
	//vgamode (0x3);
	exit ();
}
