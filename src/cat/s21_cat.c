#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int option[6] = {false};
  int pos_flag = command_analyser(argv, option);

  // for (int i = 0; i < 6; i++) {
  //   printf("%d", option[i]);
  // }

  // printf("argc = %d", argc);
  // printf(" | pos_flag = %d", pos_flag);

  while (pos_flag < argc) {
    cat(argv, pos_flag, option);
    pos_flag++;
  }
  return 0;
}

int command_analyser(char *argv[], int *option) {
  int pos_flag = 1;
  int er_flag = 0;
  while (argv[pos_flag][0] == '-') {
    if (argv[pos_flag][1] == '-') {
      er_flag = multi_flag(option, argv[pos_flag]);
    } else {
      er_flag = single_flag(option, argv[pos_flag]);
    }
    pos_flag++;
  }
  if (er_flag == 1) {
    pos_flag = -1;
  }
  return pos_flag;
}

int multi_flag(int *option, char *argv) {
  int flag = 0;
  if (strcmp(argv, "--number-nonblank") == 0) {
    option[0] = true;
  } else if (strcmp(argv, "--number") == 0) {
    option[2] = true;
  } else if (strcmp(argv, "--squeeze-blank") == 0) {
    option[3] = true;
  } else {
    flag = 1;
  }
  return flag;
}

int single_flag(int *option, char *argv) {
  int flag = 0;
  for (size_t i = 0; i < strlen(argv); i++) {
    switch (argv[i]) {
      case 'b':
        option[0] = true;
        break;
      case 'e':
        option[1] = true;
        option[5] = true;
        break;
      case 'E':
        option[1] = true;
        break;
      case 'n':
        option[2] = true;
        break;
      case 's':
        option[3] = true;
        break;
      case 't':
        option[4] = true;
        option[5] = true;
        break;
      case 'T':
        option[4] = true;
        break;
      case '?':
        flag = 1;
        break;
    }
  }
  return flag;
}

int cat(char *argv[], int pos_flag, int *option) {
  FILE *file = fopen(argv[pos_flag], "r+");
  int c;
  if (!file) {
    printf("n/a\n");
  } else {
    int n = 0;
    int new_line = true;
    int k = 1;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\n' && new_line) {
        n++;
      } else {
        n = 0;
      }

      if (n == 0 && new_line && option[0]) {
        printf("%6d\t", k);
        k++;
      }  // b
      else if (new_line && option[2] && !option[0] &&
               !(option[3] == 1 && n >= 2)) {
        printf("%6d\t", k);
        k++;
      }  // n

      if (option[3] == 1) {
        if (n >= 2) {
          continue;
        }
      }  // s
      if (c == '\n') {
        new_line = true;
      } else {
        new_line = false;
      }

      if (option[1] == 1 && c == 10 && new_line) {
        printf("$\n");
      } else if (option[4] == 1 && c == 9) {
        printf("^I");
      } else if (option[5] == 1 && c >= 127) {
        m_code(c);
      } else {
        printf("%c", c);
      }
    }
  }
  fclose(file);
  return 0;
}

void m_code(int c) {
  int s = c - 128;
  if (s <= 32 || s == 127) {
    s = s + 64;
    printf("M-^%c", s);
  } else {
    s = s - 128;
    printf("%c", s);
  }
}



// void m_code(char c) {
//   if (c <-96) {
//     printf("M-^%c", c+192);
//   } else if (c<0){
//     printf("M-%c", c+128);
//   } else if (c==9 || c == 10){
//     printf("%c", c);
//   } else if (c<32){
//     printf("^%c", c+64);
//   } else if (c<127){
//     printf("%c", c);
//   } else {
//     printf("^?");
//   }

// }