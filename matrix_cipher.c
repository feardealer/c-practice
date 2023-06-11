#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

void fillMatrix(char matrix[MAX_SIZE][MAX_SIZE],
const char * text, int size);
void printMatrix(char matrix[MAX_SIZE][MAX_SIZE], int size);
void printText(char matrix[MAX_SIZE][MAX_SIZE], int size);

void fillMatrix(char matrix[MAX_SIZE][MAX_SIZE],
  const char * text, int size) {
  int i, j, k = 0;
  for (j = 0; j < size; j++) {
    for (i = 0; i < size; i++) {
      if (k < strlen(text)) {
        matrix[i][j] = text[k];
        k++;
      } else {
        matrix[i][j] = '*';
      }
    }
  }
}

void printMatrix(char matrix[MAX_SIZE][MAX_SIZE], int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++)
      printf("%c ", matrix[i][j]);
    printf("\n");
  }
}

void printText(char matrix[MAX_SIZE][MAX_SIZE], int size) {
  int i, j;
  for (j = 0; j < size; j++) {
    for (i = 0; i < size; i++)
      printf("%c", matrix[j][i]);
  }
}

int main() {
  char matrix[MAX_SIZE][MAX_SIZE];
  char text[100];
  int size, i;

  printf("Введите текст, который хотите зашифровать: ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';

  printf("Введите размер квадратной матрицы (от 1 до %d): ", MAX_SIZE);
  scanf("%d", & size);

  if (size < 1 || size > MAX_SIZE) {
    printf("[ERROR] Неверный размер матрицы\n");
    return 1;
  }

  fillMatrix(matrix, text, size);

  printf("Матрица:\n");
  printMatrix(matrix, size);

  printf("\nШифрованный текст:\n");
  printText(matrix, size);
  printf("\n");

  return 0;
}
