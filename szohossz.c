#include <stdio.h>

int main()
{
	int hossz=0;
	int n=0x01;
	do
	{
		hossz++;
	}while(n<<=1);
	printf("Szohossz: %d bit\n",hossz);
	return 0;
}

