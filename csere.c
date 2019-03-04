#include <stdio.h>
int main()

{

int a = 10;
int b = 5;
printf("A value before: ");
printf("%d\n",a);
printf("B value before: ");
printf("%d\n",b);
	
a = a+b;
b = a-b;
a = a-b;

printf("A value after: ");
printf("%d\n",a);
printf("B value after: ");
printf("%d\n",b);
}

