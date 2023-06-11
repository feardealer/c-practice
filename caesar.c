#include <stdio.h>
#include <string.h>

void caesarEncrypt(char * message, int key) {
  int i = 0;
  int alphabetSize = 26;
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

  while (message[i] != '\0') {
    char * position = strchr(alphabet, message[i]);

    if (position != NULL) {
      int index = position - alphabet;
      message[i] = alphabet[(index + key) % alphabetSize];
    }

    ++i;
  }
}

void caesarDecrypt(char * message, int key) {
  int alphabetSize = 26;
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  int i = 0;

  while (message[i] != '\0') {
    char * position = strchr(alphabet, message[i]);

    if (position != NULL) {
      int index = position - alphabet;
      int newIndex = (index - key + alphabetSize) % alphabetSize;
      message[i] = alphabet[newIndex];
    }

    ++i;
  }
}

int main(int argc, char * argv[]) {
  FILE * fp;
  char * filename;

  if (argc < 2) {
    printf("Missing Filename\n");
    return (1);
  } else {
    filename = argv[1];
    printf("Filename : %s\n", filename);
  }

  fp = fopen(filename, "r");

  char message[1000];
  int key;

  printf("Введите ключ (сдвиг): ");
  scanf("%d", & key);

  while (fgets(message, sizeof(message), fp)) {
    if (strlen(message) > 0 && message[strlen(message) - 1] == '\n') {
      message[strlen(message) - 1] = '\0';
    }

    caesarEncrypt(message, key);
    printf("Зашифрованное сообщение: %s\n", message);

    caesarDecrypt(message, key);
    printf("Расшифрованное сообщение: %s\n", message);
  }

  return 0;
}
