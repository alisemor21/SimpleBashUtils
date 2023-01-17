#include "s21_grep.h"

int output_no_flag(char argv[], char *optarg) {
  char *line = NULL;
  int k = 1;
  size_t len = 0;
  ssize_t c;
  regex_t regex;

  // printf("ФАЙЛ: %s\nШАБЛОН: %s\n\n\n", argv, optarg);

  regcomp(&regex, optarg, 0);

  FILE *file = fopen(argv, "r+");
  if (!file) {
    printf("no file n/a\n");
  } else {
    while ((c = getline(&line, &len, file)) != -1) {
      int status = regexec(&regex, line, 0, NULL, 0);
      if (status == 0) {
        printf("%s", line);
      }
      k++;
    }
    free(line);
    fclose(file);
  }

  regfree(&regex);
  return 0;
}

int l_function(int argc, char *argv[], char *optarg) {
  int s = 3;
  while (s < argc) {
    char *line = NULL;
    size_t len = 0;
    ssize_t c;
    regex_t regex;
    regcomp(&regex, optarg, 0);
    FILE *file = fopen(argv[s], "r");
    if (!file) {
      printf("n/a\n");
    } else {
      while ((c = getline(&line, &len, file)) != -1) {
        int status = regexec(&regex, line, 0, NULL, 0);
        if (status == 0) {
          printf("%s\n", argv[s]);
          break;
        }
      }
      free(line);
      fclose(file);
    }
    s++;
    regfree(&regex);
  }
  return 0;
}

int h_function(int argc, char *argv[], char *optarg) {
  int s = 3;
  while (s < argc) {
    char *line = NULL;
    size_t len = 0;
    ssize_t c;
    regex_t regex;
    regcomp(&regex, optarg, 0);

    FILE *file = fopen(argv[s], "r+");
    if (!file) {
      printf("n/a\n");
    } else {
      while ((c = getline(&line, &len, file)) != -1) {
        int status = regexec(&regex, line, 0, NULL, 0);
        if (status == 0) {
          printf("%s", line);
        }
      }
      free(line);
      fclose(file);
    }
    s++;
    regfree(&regex);
  }
  return 0;
}

int f_function(int argc, char *argv[], char *optarg) {
  char *line_pat = NULL;
  char *line = NULL;
  size_t len_pat = 0;
  size_t len = 0;
  ssize_t c;
  regex_t regex;

  // printf("файл с шаблоном: %s\n", optarg);
  FILE *file_pat = fopen(optarg, "r");
  // printf("файл с текстом: %s\n", argv[argc-1]);
  if (!file_pat) {
    printf("n/a\n");
  } else {
    fclose(file_pat);
    FILE *file = fopen(argv[argc - 1], "r");

    if (!file) {
      printf("n/a\n");
    } else {
      while ((c = getline(&line, &len, file)) != -1) {
        // printf("%s - из файла\n", line);
        FILE *file_pat = fopen(optarg, "r");
        while ((c = getline(&line_pat, &len_pat, file_pat)) != -1) {
          if (line_pat[c - 1] == '\n' && c == 1) {
            regcomp(&regex, ".", REG_EXTENDED);
          } else {
            line_pat[c - 1] = '\0';
            regcomp(&regex, line_pat, REG_EXTENDED);
          }
          int status = regexec(&regex, line, 0, NULL, 0);
          if (status == 0) {
            printf("%s", line);
            regfree(&regex);
            break;
          }
          regfree(&regex);
        }
        fclose(file_pat);
      }
      free(line_pat);
      free(line);
      fclose(file);
    }
  }
  return 0;
}

int output(char flag, char argv[], char *optarg) {
  char *line = NULL;
  int k = 1;
  int n = 0;
  size_t len = 0;
  ssize_t c;
  regex_t regex;

  // printf("СЛОВ: %d\nФАЙЛ: %s\nШАБЛОН: %s\n\n\n", argc, argv, optarg);

  if (flag == 'i') {
    regcomp(&regex, optarg, REG_ICASE);
  } else {
    regcomp(&regex, optarg, 0);
  }

  FILE *file = fopen(argv, "r+");
  if (!file) {
    if (flag != 's') {
      printf("no file n/a\n");
    }

  } else {
    while ((c = getline(&line, &len, file)) != -1) {
      if (flag == 'e' || flag == 'i' || flag == 'n' || flag == 's') {
        int status = regexec(&regex, line, 0, NULL, 0);
        if (status == 0) {
          if (flag == 'n') {
            printf("%d:", k);
          }

          printf("%s", line);
        }
        k++;
      }
      if (flag == 'v') {
        int status = regexec(&regex, line, 0, NULL, 0);
        if (status != 0) {
          printf("%s", line);
        }
      }
      if (flag == 'c') {
        int status = regexec(&regex, line, 0, NULL, 0);
        if (status == 0) {
          n++;
        }
      }
    }
    if (flag == 'c') {
      printf("%d\n", n);
    }
    free(line);
    fclose(file);
  }
  regfree(&regex);
  return 0;
}

int main(int argc, char *argv[]) {
  int res;
  int w = optind;
  int f = 0;

  if (argc == 3) {
    f = 1;
    output_no_flag(argv[argc - 1], argv[argc - 2]);
  }

  while ((res = getopt(argc, argv, "e:i:v:c:l:n:h:s:f:")) != -1 && w < argc &&
         f == 0) {
    switch (res) {
      case 'e':
        output(res, argv[optind], optarg);
        break;
      case 'i':
        output(res, argv[optind], optarg);
        break;
      case 'v':
        output(res, argv[optind], optarg);
        break;
      case 'c':
        output(res, argv[optind], optarg);
        break;
      case 'l':
        l_function(argc, argv, optarg);
        break;
      case 'n':
        output(res, argv[optind], optarg);
        break;
      case 'h':
        h_function(argc, argv, optarg);
        break;
      case 's':
        output(res, argv[optind], optarg);
        break;
      case 'f':
        f_function(argc, argv, optarg);
        break;
      default:
        break;
    }
    w++;
  }
  return 0;
}
