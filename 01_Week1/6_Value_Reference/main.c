
#include <stdio.h>
#include <string.h>

void modify(int x, char text[])
{
	x++;
	text[0]--;
}

int main()
{
	int v = 5;
	char name[5] = "Good";
	printf("v = %d, name = %s\r\n", v, name);
	modify(v, name);
	printf("v = %d, name = %s\r\n", v, name);

	return 0;
}
