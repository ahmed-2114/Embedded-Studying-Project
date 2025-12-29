/*
 * main.c
 *
 *  Created on: Oct 7, 2024
 *      Author: ahmed
 */


#include <stdio.h>

enum Gender{MALE, FEMALE};

struct SPerson
{
	char m_Name[100];
	enum Gender m_Gender;
};

void main()
{
	int i;
	struct SPerson persons[] = {{"Ahmed Ali", MALE},
								{"Mona Mohamed", FEMALE}};

	for(i=0; i<sizeof(persons)/sizeof(struct SPerson); i++)
	{
		printf("%s - %s\n", persons[i].m_Name,
				(persons[i].m_Gender == MALE)?"Male":"Female");
	}
}
