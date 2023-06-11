#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#define MAX 1000

int dec_to_bin(int N);
int bin_to_dec(int N);
double bin_to_dec_fractional(char bin_fractional[MAX]);
double dec_to_bin_fractional(char dec_fractional[MAX]);
int my_pow(int x, int y);
int my_atoi(char s[]);

int main(int argc, char * argv[]) {
  if (argc == 1) {
    while (true) {
      printf("%s\n", "[1] - Decimal to binary");
      printf("%s\n", "[2] - Binary to decimal");
      printf("%s\n", "[3] - Decimal to binary (fractional)");
      printf("%s\n", "[4] - Binary to decimal (fractional)");
      printf("%s\n", "[0] - Exit");

      int choice = 0;
      printf("%s", "Action: ");
      scanf("%d", & choice);

      if (choice == 1) {
        int number;
        printf("%s", "Decimal: ");
        scanf("%d", & number);
        printf("%s", "Binary: ");
        printf("%d\n", dec_to_bin(number));
      }
      if (choice == 2) {
        int number;
        printf("%s", "Binary: ");
        scanf("%d", & number);
        printf("%s", "Decimal: ");
        printf("%d\n", bin_to_dec(number));

      }
      if (choice == 3) {
        char fractional_dec[MAX];
        printf("%s", "Decimal: ");
        scanf("%s", fractional_dec);
        printf("%s", "Binary: ");
        printf("%lf\n", dec_to_bin_fractional(fractional_dec));

      }
      if (choice == 4) {
        char fractional_bin[MAX];
        printf("%s", "Binary: ");
        scanf("%s", & fractional_bin);
        printf("%s", "Decimal: ");
        printf("%lf\n", bin_to_dec_fractional(fractional_bin));

      }
      if (choice == 0) {
        printf("%s\n", "Good luck.");
        return 1;
      }
      if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0) {
        printf("%s\n", "Wrong choice!");
        return 1;
      }
    }
  }

  if (argc == 3) {
    int number = my_atoi(argv[2]);

    if (strcmp(argv[1], "dec2bin") == 0) {
      printf("%i\n", dec_to_bin(number));
    }
    if (strcmp(argv[1], "bin2dec") == 0) {
      printf("%i\n", bin_to_dec(number));
    }
    if (strcmp(argv[1], "bin2decfract") == 0) {
      printf("%lf\n", bin_to_dec_fractional(argv[2]));
    }
    if (strcmp(argv[1], "dec2binfract") == 0) {
      printf("%lf\n", dec_to_bin_fractional(argv[2]));
    }
  }

  if (argc == 2) {
    printf("%s\n", "Too few args.");
    return 1;
  }
  if (argc > 3) {
    printf("%s\n", "Too much args.");
    return 1;
  }
  return 0;
}

int dec_to_bin(int N) {
  int bin = 0, x = 1;
  while (N) {
    bin += (N % 2) * x;
    x *= 10;
    N /= 2;
  }
  return bin;
}

int bin_to_dec(int N) {
  int dec = 0, x = 0, r;

  while (N != 0) {
    r = N % 10;
    N /= 10;
    dec += r * my_pow(2, x);
    ++x;
  }
  return dec;

}

double bin_to_dec_fractional(char fractional_bin[MAX]) {
  long double fractional_dec = 0.0, dFractional = 0.0, fraFactor = 0.5;
  long int dIntegral = 0, bIntegral = 0, bFractional[MAX];
  long int intFactor = 1, remainder, i = 0, k = 0, flag = 0;

  while (fractional_bin[i]) {

    if (fractional_bin[i] == '.')
      flag = 1;
    else if (flag == 0)
      bIntegral = bIntegral * 10 + (fractional_bin[i] - 48);
    else
      bFractional[k++] = fractional_bin[i] - 48;
    i++;
  }

  while (bIntegral != 0) {
    remainder = bIntegral % 10;
    dIntegral = dIntegral + remainder * intFactor;
    intFactor = intFactor * 2;
    bIntegral = bIntegral / 10;
  }

  for (i = 0; i < k; i++) {
    dFractional = dFractional + bFractional[i] * fraFactor;
    fraFactor = fraFactor / 2;
  }

  fractional_dec = dIntegral + dFractional;

  return fractional_dec;
}

double dec_to_bin_fractional(char fractional_dec[MAX]) {

}

int my_pow(int x, int y) {
  int power = 1, i;
  for (i = 1; i <= y; ++i)
    power = power * x;

  return power;
}

int my_atoi(char s[]) {
  int i, n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    n = 10 * n + (s[i] - '0');

  return n;
}

/*
TODO:
Make function which translates decimal to binary (fractional mode)
*/
