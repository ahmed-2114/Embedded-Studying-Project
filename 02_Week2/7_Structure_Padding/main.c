/*
 * main.c
 *
 *  Created on: Oct 6, 2024
 *      Author: ahmed
 */

#include <stdio.h>

void dump_memory(char *ptr, int size);

struct Sdata{
	unsigned char data1;
	unsigned int data2;
	unsigned char data3;
	unsigned short data4;
};

struct Sdata gdata;

void main()
{
	gdata.data1 = 0xAA;
	gdata.data2 = 0xFFFFFFFF;
	gdata.data3 = 0x55;
	gdata.data4 = 0xA5A5;

	int total_size = sizeof(struct Sdata);
	dump_memory(&gdata, total_size);
}

void dump_memory(char *ptr, int size)
{
	int i;
	for (i=0; i<size; i++)
	{
		printf("%p\t%X\n", ptr, (unsigned char)*ptr);
		ptr++;
	}
}
