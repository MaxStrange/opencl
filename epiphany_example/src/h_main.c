#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <e-hal.h>
#include <stdio.h>
#include "common.h"

int main(int argc, char *argv[])
{
	e_platform_t platform;
	e_epiphany_t dev;

	int a[N], b[N], c[CORES];
	int clr;
	clr = (int)0x00000000;

	printf("Calculating the dot product of two vectors of length 4096, where all elements of vector a are initialized to 1 and all those in vector b are initialized to 2.\n");
	printf("................\n");

	//Initialize Device
	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);
	e_open(&dev, 0, 0, platform.rows, platform.cols);

	//Initialize a and b input vectors on the host
	int i;
	for (i = 0; i < N; i++)
	{
		a[i] = 1;
		b[i] = 2;
	}

	//Load program to cores
	e_load_group("e_task.elf", &dev, 0, 0, platform.rows, platform.cols, E_FALSE);

	//Copy the data from the host to the device and clear the done flag for each core
	int j, k;
	for (j = 0; j < platform.rows; j++)
	{
		for (k = 0; k < platform.cols; k++)
		{
			e_write(&dev, j, k, 0x2000, &a, (N/CORES) * sizeof(int));
			e_write(&dev, j, k, 0x4000, &b, (N/CORES) * sizeof(int));
			e_write(&dev, j, k, 0x7000, &clr, sizeof(clr));
		}
	}

	//Do the task!
	e_start_group(&dev);

	//Wait until all cores are done
	int done[CORES];
	int all_done = 0;
	while (all_done != CORES)
	{
		all_done = 0;
		i = 0;
		j = 0;
		for (i = 0; i < platform.rows; i++)
		{
			for (j = 0; j < platform.cols; j++)
			{
				e_read(&dev, i, j, 0x7000, &done[i * platform.cols + j],
                        sizeof(int));
				all_done += done[i * platform.cols + j];
			}
		}	
	}

	//Copy all device results back to host memory
	for (i = 0; i < platform.rows; i++)
	{
		for (j = 0; j < platform.cols; j++)
		{
			e_read(&dev, i, j, 0x6000, &c[i * platform.cols + j], sizeof(int));
		}
	}

	//Calculate the final sum
	int sum = 0;
	for (i = 0; i < CORES; i++)
	{
		sum += c[i];
	}

	// Now calculate what it SHOULD be
	int cpu_sum = 0;
	int cpu_a[N];
	int cpu_b[N];
	for (i = 0; i < N; i++)
	{
		cpu_a[i] = 1;
		cpu_b[i] = 2;
	}
	for (i = 0; i < N; i++)
	{
		cpu_sum += cpu_a[i] * cpu_b[i];
	}

	//The total sum is:
	printf("The total sum is: %d\n", sum);
	printf("The total sum SHOULD be: %d\n", cpu_sum);
	fflush(stdout);

	//Turn off the device
	e_close(&dev);
	e_finalize();
}













