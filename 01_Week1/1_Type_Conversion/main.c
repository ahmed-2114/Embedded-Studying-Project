

//#include "stdio.h"
//int main()
//{
//	int x =5;
//	float y = 2.0;
//	if(x/y == 2)
//	{
//		printf("int/float >>> int \n");
//	}
//	else if (x/y == 2.5)
//	{
//		printf("int/float >>> float \n");
//	}
//}

#include "stdio.h"
#include "math.h"
int main()
{
int a = 9;
int b = 8;
int c = 12;
printf("%d\n", a>b);
printf("%d\n", b>c);
printf("%d\n", a<=9);
printf("%d\n", a!=9);
printf("%d\n", (a-b)>(c-b));
printf("%d\n", a>b && c>b);
printf("%d\n", a>b && c<b);
printf("%d\n", a>b || c<b);
printf("%d\n", !(a<b));
printf("%d\n", 3 && 0);
printf("%d\n", -15 || 0);
printf("%d\n", !(-15));
return 0;
}


