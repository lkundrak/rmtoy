/* Has to be first */

void
main ()
{
	vgamode (0x13);
	draw();
	dumpvga ();
	//vgamode (0x3);
	exit ();
}
