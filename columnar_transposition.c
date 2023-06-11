#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 1000

int get_size (char *, int);
void string_input(char str[], int nchars);
void encrypt (char *, int, int);
 
int main (int argc, char *argv[]) {
	int rows, columns;
    	char string[STRING_LENGTH];

	printf("Кол-во строк: ");
	scanf("%d", &rows);
	
	scanf("%s", string);
	
	if (rows < 1) {
		printf("Error..\n");
		return 1;
	}

	columns = get_size(string, rows);
	encrypt(string, rows, columns);
	return 0;
}

int get_size (char *string, int rows) {
	int d = strlen(string);
	return (d - 1) / rows + 1;
}

void string_input(char str[], int nchars) {
	int i = 0, c;
  	while ((c = getchar()) != '\n' && c != EOF ) {
    		if (i < nchars) {
			if (c == ' ')
				str[i++] = '_';
			else
	    			str[i++] = c;
		}
	}
	str[i] = '\0';
}

void encrypt (char *string, int rows, int columns) {
	int i, j, index, length = strlen(string);
	char c;

	for (i = 0; i < columns; ++i) {
        	for (j = 0; j < rows; ++j) {
            		index = (j * columns) + i;
            		
			if (index >= length)
				c = '*';
            		else c = string[index];
            		
			printf("%c\n", c);
        	}
    	}
	putchar('\n');
}
