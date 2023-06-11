#include <stdio.h>
#define MAX_FILE_NAME 100

int main(int argc, char *argv[])
{

	if (argc == 2) {
		FILE *fp;
    char filename[MAX_FILE_NAME];
    char c;

		fp = fopen(argv[1], "r");
  
    if (fp == NULL) {
      printf("%s: cannot access '%s': No such file or directory", argv[0], argv[1]);
			return 1;
    }

		while ((c = fgetc(fp)) != EOF)
		  putchar(c);

		fclose(fp);

	} else {
		printf("Usage: ./a.out text.txt");
		return 1;
	}
	return 0;
}
