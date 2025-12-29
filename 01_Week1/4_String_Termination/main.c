
#include <stdio.h>

int main(void)
{
	char text1[] = {'h', 'e', 'l', 'l', 'o', 0};
	char text2[] = {"hello"};
	char text3[] = "hello";

	printf("%s %s %s", text1, text2, text3);
}
