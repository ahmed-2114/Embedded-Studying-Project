
#include <stdio.h>

int main(void)
{
	int a, b, c, min;
	printf("enter 3 numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d %d", &a, &b, &c);
	min = (a<b) ? ((a<c) ? a : c) : ((b<c) ? b : c);
	printf("the smallest number is: %d", min);
}

