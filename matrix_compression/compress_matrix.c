#include <stdio.h>

#define SIZE 10

void compressMatrix(int matrix[][SIZE]) {
  int compressedMatrix[SIZE][2];
  int compressedSize = 0;

  for (int i = 0; i < SIZE; i++) {
    int count = 0;

    for (int j = 0; j < SIZE; j++) {
      if (matrix[i][j] == 1) {
        count++;
      }
    }

    if (count > 0) {
      compressedMatrix[compressedSize][0] = i;
      compressedMatrix[compressedSize][1] = count;
      compressedSize++;
    }
  }

  printf("Исходная матрица:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  size_t originalSize = SIZE * SIZE * sizeof(int);
  printf("Размер исходной матрицы: %zu байт\n", originalSize);

  printf("Сжатая матрица:\n");
  for (int i = 0; i < compressedSize; i++) {
    printf("(%d, %d) ", compressedMatrix[i][0], compressedMatrix[i][1]);
  }
  printf("\n");

  size_t compressedSizeBytes = compressedSize * 2 * sizeof(int);
  printf("Размер сжатой матрицы: %zu байт\n", compressedSizeBytes);
}

int main() {
  int matrix[SIZE][SIZE];

  FILE * file = fopen("matrix.txt", "r");
  if (file == NULL) {
    printf("Ошибка открытия файла\n");
    return 1;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      fscanf(file, "%d", & matrix[i][j]);
    }
  }

  fclose(file);

  compressMatrix(matrix);

  return 0;
}
