#include <stdio.h>

double A_1 = 0;
double A_2 = 0;

double find_delta(double A)
{
	double delta = A;
	while (1) {
		if (A == A + delta/2.0) {
			A_2 = A + delta/2.0;
			return delta;
      			break;
		}
		A_1 = A + delta;
		
		delta /= 2.0;
	}
}
int main()
{
	double A;
	scanf("%lf", &A);
	printf("Delta: %.20lf\n", find_delta(A)); 
	printf("A + delta != A %.20lf\n", A_1);
	printf("A + delta/2 = A %.20lf\n", A_2);
	return 0;
}

// A + delta != A
// A + delta/2 = A
