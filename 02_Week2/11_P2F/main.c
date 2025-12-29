/*
 * main.c
 *
 *  Created on: Oct 7, 2024
 *      Author: ahmed
 */


#include <stdio.h>

void (* PFun)();

void print_embedded()
{
	printf("Embedded Systems\n");
}

int main()
{
	print_embedded();
	PFun = print_embedded;
	PFun();
}
