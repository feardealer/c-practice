#include <stdio.h>

int main(int argc, char *argv[])
{
	//float a, b;
	//double a, b;
	long double a, b;

	a = 167772216.0;
	b = 167772217.1;

	printf("%Lf\n", a - b);

	return 0;
}

// float - not work
// double - work
// long double - not work 
// why?
