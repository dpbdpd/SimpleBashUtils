#include "s21_cat.h"

void print_with_line_numbers(FILE* file, bool flag_b, bool flag_n) {
  int line_number = 1;
  char c;
  bool is_empty_line = true;  // Флаг, указывающий на пустую строку

  while ((c = fgetc(file)) != EOF) {
    if (flag_b && is_empty_line && c != '\n') {
      printf("%6d\t", line_number++);
      is_empty_line = false;
    }

    if (flag_n && is_empty_line) {
      printf("%6d\t", line_number++);
      is_empty_line = false;
    }

    putchar(c);

    if (c == '\n') {
      is_empty_line = true;
    }
  }
}

void print_with_blank_lines(FILE* file) {
  char c;
  bool is_prev_line_empty =
      false;  // Флаг указывающий, является ли предыдущая строка пустой
  bool is_current_line_empty =
      true;  // Флаг указывающий, является ли текущая строка пустой

  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      if (is_current_line_empty) {
        if (!is_prev_line_empty) {
          putchar(c);
        }
        is_prev_line_empty = true;
      } else {
        putchar(c);
        is_prev_line_empty = false;
      }
      is_current_line_empty = true;
    } else {
      putchar(c);
      is_current_line_empty = false;
      is_prev_line_empty = false;
    }
  }
}

void print_with_tabs(FILE* file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c != '\n') {
      if (c >= 0 && c <= 31) {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^%c", c - 64);
      } else {
        printf("%c", c);
      }
    } else
      printf("%c", c);
  }
}

void print_with_tabs_T(FILE* file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\t') {
      printf("^I");
    } else {
      printf("%c", c);
    }
  }
}

void print_with_ends(FILE* file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c != '\n') {
      if (c >= 0 && c <= 31 && c != 9) {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^%c", c - 64);
      } else {
        printf("%c", c);
      }
    } else
      printf("$%c", c);
  }
}

void print_with_ends_E(FILE* file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      printf("$\n");
    } else {
      printf("%c", c);
    }
  }
}

void print_with_nonprinting_chars(FILE* file) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c != '\n') {
      if (c >= 0 && c <= 31 && c != 9) {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^%c", c - 64);
      } else {
        printf("%c", c);
      }
    } else
      printf("%c", c);
  }
}

int main(int argc, char* argv[]) {
  FILE* file;
  int opt;
  bool flag_b = false, flag_e = false, flag_n = false, flag_s = false,
       flag_t = false, flag_v = false, flag_E = false, flag_T = false;
  while ((opt = getopt(argc, argv, "benstvET")) != -1) {
    switch (opt) {
      case 'b':
        flag_b = true;
        break;
      case 'e':
        flag_e = true;
        flag_v = true;
        break;
      case 'n':
        flag_n = true;
        break;
      case 's':
        flag_s = true;
        break;
      case 't':
        flag_t = true;
        break;
      case 'v':
        flag_v = true;
        break;
      case 'E':
        flag_E = true;
        break;
      case 'T':
        flag_T = true;
        break;
      default:
        fprintf(stderr, "Usage: %s [-benstvET] [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  for (int i = optind; i < argc; i++) {
    file = fopen(argv[i], "r");
    if (file == NULL) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }

    if (flag_b || flag_n) {
      print_with_line_numbers(file, flag_b, flag_n);
    }
    if (flag_e) {
      print_with_ends(file);
    }
    if (flag_s) {
      print_with_blank_lines(file);
    }
    if (flag_t) {
      print_with_tabs(file);
    }
    if (flag_v) {
      print_with_nonprinting_chars(file);
    }
    if (flag_E) {
      print_with_ends_E(file);
    }
    if (flag_T) {
      print_with_tabs_T(file);
    } else {
      char c;
      while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
      }
    }

    fclose(file);
  }

  return 0;
}