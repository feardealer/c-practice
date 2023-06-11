#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static int iMatrixRange = 0;
static char * pMaskArr = NULL;
static FILE * pSrcFile = NULL;
static FILE * pDstFile = NULL;

static void FlipHorisontally() {
  for (int ii = 0; ii < iMatrixRange; ++ii) {
    for (int jj = 0; jj < (iMatrixRange / 2); ++jj) {
      char cTemp = pMaskArr[ii * iMatrixRange + jj];

      int kk = (iMatrixRange - 1) - jj;

      pMaskArr[ii * iMatrixRange + jj] = pMaskArr[ii * iMatrixRange + kk];
      pMaskArr[ii * iMatrixRange + kk] = cTemp;
    }
  }
}

static void FlipVertically() {
  for (int jj = 0; jj < iMatrixRange; ++jj) {
    for (int ii = 0; ii < (iMatrixRange / 2); ++ii) {
      char cTemp = pMaskArr[ii * iMatrixRange + jj];

      int kk = (iMatrixRange - 1) - ii;

      pMaskArr[ii * iMatrixRange + jj] = pMaskArr[kk * iMatrixRange + jj];
      pMaskArr[kk * iMatrixRange + jj] = cTemp;
    }
  }
}

static void Encrypt() {
  int iCnt = 0;
  int iReadCnt = 0;

  char * pTextArr = (char * ) malloc(iMatrixRange * iMatrixRange);

  if (!pTextArr) {
    printf("Ошибка. Нехватка памяти.\n");
    return;
  }

  memset(pTextArr, 0, iMatrixRange * iMatrixRange);

  while (1) {
    for (int ii = 0; ii < iMatrixRange; ++ii) {
      for (int jj = 0; jj < iMatrixRange; ++jj) {
        if (pMaskArr[ii * iMatrixRange + jj] == '*') {
          int Chr = fgetc(pSrcFile);

          if (Chr == EOF) {
            goto FINISH;
          }

          ++iReadCnt;

          pTextArr[ii * iMatrixRange + jj] = (char) Chr;
        }
      }
    }

    ++iCnt;

    if ((iCnt == 1) || (iCnt == 3)) {
      FlipHorisontally();
    }

    if ((iCnt == 2) || (iCnt == 4)) {
      FlipVertically();
    }

    if (iCnt == 4) {
      for (int kk = 0; kk < (iMatrixRange * iMatrixRange); ++kk) {
        fprintf(pDstFile, "%c", pTextArr[kk]);
      }

      memset(pTextArr, 0, iMatrixRange * iMatrixRange);

      iReadCnt = 0;
    }

    iCnt %= 4;
  }

  FINISH:

    if (iReadCnt) {
      for (int kk = 0; kk < iMatrixRange * iMatrixRange; ++kk) {
        fprintf(pDstFile, "%c", pTextArr[kk]);
      }
    }

  if (pTextArr) {
    free(pTextArr);
  }
}

static void Decrypt() {
  int iCnt = 0;
  int iWriteCnt = 0;

  char * pTextArr = (char * ) malloc(iMatrixRange * iMatrixRange);

  if (!pTextArr) {
    printf("Ошибка. Нехватка памяти.\n");
    return;
  }

  memset(pTextArr, 0, iMatrixRange * iMatrixRange);

  fseek(pSrcFile, 0 L, SEEK_END);
  iWriteCnt = ftell(pSrcFile);
  fseek(pSrcFile, 0 L, SEEK_SET);

  fread(pTextArr, iMatrixRange * iMatrixRange, 1, pSrcFile);

  while (1) {
    for (int ii = 0; ii < iMatrixRange; ++ii) {
      for (int jj = 0; jj < iMatrixRange; ++jj) {
        if (pMaskArr[ii * iMatrixRange + jj] == '*') {
          fprintf(pDstFile, "%c", pTextArr[ii * iMatrixRange + jj]);
          --iWriteCnt;

          if (!iWriteCnt) {
            goto FINISH;
          }
        }
      }
    }

    ++iCnt;

    if ((iCnt == 1) || (iCnt == 3)) {
      FlipHorisontally();
    }

    if ((iCnt == 2) || (iCnt == 4)) {
      FlipVertically();
    }

    if (iCnt == 4) {
      memset(pTextArr, 0, iMatrixRange * iMatrixRange);

      fread(pTextArr, 1, iMatrixRange * iMatrixRange, pSrcFile);
    }

    iCnt %= 4;
  }

  FINISH:

    if (pTextArr) {
      free(pTextArr);
    }
}

static void ShowHelp() {
  const char pszDescript[] = "Cardan Grille Cipher";

  printf("%s\n\n", pszDescript);
  printf("Usage: ./a.out {e|E|d|D} msk.txt src.txt dst.txt\n\n");
  printf("Where:\n");
  printf("   e|E - Encrypt\n");
  printf("   d|D - Decrypt\n");
  printf("   msk - Mask file\n");
  printf("   src - Source file\n");
  printf("   dst - Destination file\n\n");
}

int main(int argc, char ** argv) {
  FILE * pMaskFile = NULL;

  if (argc != 5) {
    ShowHelp();
    return 0;
  }

  pMaskFile = fopen(argv[2], "rb");

  fseek(pMaskFile, 0 L, SEEK_END);
  iMatrixRange = ftell(pMaskFile);
  fseek(pMaskFile, 0 L, SEEK_SET);

  iMatrixRange = (int) sqrt(iMatrixRange);

  if (iMatrixRange < 4) {
    printf("Неверный ранг матрицы - %d\nРанг матрицы должен быть не меньше 4.\n", iMatrixRange);
    return -1;
  }

  if (iMatrixRange > 255) {
    printf("Неверный ранг матрицы - %d\nРанг матрицы должен быть не больше 255.\n", iMatrixRange);
    return -1;
  }

  pMaskArr = (char * ) calloc(iMatrixRange * iMatrixRange, sizeof(char));

  if (!pMaskArr) {
    printf("Ошибка. Нехватка памяти.\n");
    return -1;
  }

  fread(pMaskArr, iMatrixRange * iMatrixRange, 1, pMaskFile);

  fclose(pMaskFile);

  switch ( * argv[1]) {
  case 'e':
  case 'E': {
    pSrcFile = fopen(argv[3], "rb");
    pDstFile = fopen(argv[4], "wb");

    if (pSrcFile && pDstFile) {
      Encrypt();
      fclose(pSrcFile);
      fclose(pDstFile);
    } else {
      printf("Ошибка открытия файла.\n");
    }

    break;
  }
  case 'd':
  case 'D': {
    pSrcFile = fopen(argv[3], "rb");
    pDstFile = fopen(argv[4], "wb");

    if (pSrcFile && pDstFile) {
      Decrypt();
      fclose(pSrcFile);
      fclose(pDstFile);
    } else {
      printf("Ошибка открытия файла.\n");
    }

    break;
  }
  default: {
    printf("Неверная операция %c.\nДопустимые операции e|E - Encrypt и d|D - Decrypt.\n", * argv[2]);
    break;
  }
  }

  if (pMaskArr) {
    free(pMaskArr);
    pMaskArr = NULL;
  }

  return 0;
}
