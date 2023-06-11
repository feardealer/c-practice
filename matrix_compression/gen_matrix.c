#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void generateMatrixToFile() {
  int matrix[SIZE][SIZE];

  srand(time(NULL));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      matrix[i][j] = rand() % 2;
    }
  }

  FILE * file = fopen("matrix.txt", "w");
  if (file == NULL) {
    printf("Ошибка открытия файла\n");
    return;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      fprintf(file, "%d ", matrix[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);

  printf("Матрица сохранена в файл matrix.txt\n");
}

int main() {
  generateMatrixToFile();
  return 0;
}
