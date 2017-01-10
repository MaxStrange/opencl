#include <stdio.h>
#include <stdlib.h>

#include "e-lib.h"
#include "common.h"

int main(void)
{
	unsigned *a, *b, *c, *d;
	int i;

	a = (unsigned *) 0x2000;//Address of matrix a
	b = (unsigned *) 0x4000;//Address of matrix b
	c = (unsigned *) 0x6000;//Result
	d = (unsigned *) 0x7000;//Done

	//Clear sum
	(*(c)) = 0x0;

	//Sum of product calculation
	for (i = 0; i < N / 16; i++)
	{
		// I think there's supposed to be
		// an offset into each matrix
		// according to which core you are
		(*(c)) += a[i] * b[i];
	}

	//Raising "done" flag
	(*(d)) = 0x00000001;

	//Put core in idle state
	__asm__ __volatile__("idle");
}

