#include <stdio.h>

int main()
{
  long dec, q, remainder;
  int i, j = 0;

  char hex[100];

  printf("Enter dec number: ");
	scanf("%ld", &dec);

	q = dec;

  while (q != 0)
	{
    remainder = q % 16;
        	
	  if (remainder < 10)
      hex[j++] = 48 + remainder;

    else	
		  hex[j++] = 55 + remainder;
    
    q /= 16;

  }

  for (i = j; i >= 0; i--)
    printf("%c", hex[i]);
  
  puts("\n");
	return 0;
}
