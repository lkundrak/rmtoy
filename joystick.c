/* Has to be first */
void
main ()
{
	int barx = 39;
	int bary = 12;
	int oldx = 0, oldy = 0;

	clear ();
	while (1) {
		int port;
		int x, y;
		int changed;

		if (oldx != barx || oldy != bary)
			bar (oldx, oldy, 1, ' ');
		bar (barx, bary, 1, 0xdb);

		oldx = barx;
		oldy = bary;

		port = normread (&x, &y);
		if (!(port & 0x30))
			exit ();

		if (x < 2) {
			barx--;
		} else if (x > 5) {
			barx++;
		}

		if (y < 2) {
			bary--;
		} else if (y > 5) {
			bary++;
		}

		if (barx < 0)
			barx = 0;
		if (barx > 78)
			barx = 78;
		if (bary < 0)
			bary = 0;
		if (bary > 24)
			bary = 24;
	}
}

int
normread (x, y)
	int *x, *y;
{
	static int minx, maxx = 0;
	static int miny, maxy;
	int port;
	register scratch;

	port = stick (x, y);
	if (!maxx) {
		minx = maxx = *x;
		miny = maxy = *y;
	}
	if (*x > maxx)
		maxx = *x;
	if (*x < minx)
		minx = *x;
	if (*y > maxy)
		maxy = *y;
	if (*y < miny)
		miny = *y;

#if 0		
	printf ("b1:%c b2:%c port=0x%x x:(%d,%d,%d), y:(%d,%d,%d)\n",
		port & 0x10 ? '-' : '+',
		port & 0x20 ? '-' : '+',
		port,
		minx, *x, maxx,
		miny, *y, maxy);
#endif
        scratch = ((maxy - miny) / 6);
	if (scratch) {
		*y = (*y - miny) / scratch;
	} else {
		*y = 3;
	}

        scratch = ((maxx - minx) / 6);
	if (scratch) {
		*x = (*x - minx) / scratch;
	} else {
		*x = 3;
	}

	return port;
}

#if 0
int
readjoy (x, y)
	int *x, *y;
{
	int port;

	*x = *y = 0;
	outb (0x201, 0xff);

	do {
		port = inb (0x201);
		if (port & 1)
			(*x)++;
		if (port & 2)
			(*y)++;

		// A timeout
		//if (*x + *y > 1024)
		//	return -1;
	} while (port & 3);

	return port;
}
#endif
