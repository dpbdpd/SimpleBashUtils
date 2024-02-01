#include "s21_grep.h"

int main(int argc, char *argv[]) {  // принимаем аргументы командной строки
  if (argc > 1) {
    char *template = NULL;  // указатель на шаблон
    set_settings(&argument);
    set_options(argc, argv, &argument, &template);  // обработка командной стоки
    for (int t = optind; t < argc; t++) {  // цикл перебора файлов
      open_file(argv[t], &argument, template);
    }
    free(template);  // освобождаем память выделенную под шаблон
  } else
    fprintf(
        stderr,
        "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B num] "
        "[-C[num]]"
        "[-e pattern] [-f file] [--binary-files=value] [--color=when]"
        "[--context[=num]] [--directories=action] [--label] [--line-buffered]"
        "[--null] [pattern] [file ...]");

  return 0;
}

void set_options(int argc, char *argv[], struct arguments *argument,
                 char **template) {
  for (int sym = 0;
       (sym = getopt_long(argc, argv, "ivclne:", 0, NULL)) != (-1);) {
    switch (sym) {
      case 'i':
        argument->arg_i = 1;
        break;
      case 'v':
        argument->arg_v = 1;
        break;
      case 'c':
        argument->arg_c = 1;
        break;
      case 'l':
        argument->arg_l = 1;
        break;
      case 'n':
        argument->arg_n = 1;
        break;
      case 'e':
        argument->arg_e = 1;
        config_E(optarg, template);
        break;
    }
  }
  if (argument->arg_e == 0) {
    create_template(template, argv[optind]);
    optind += 1;
  }

  argument->arg_file = argc - optind;
}

void open_file(char *file, struct arguments *argument, char *template) {
  regex_t rx;
  int flag_i =
      (argument->arg_i) ? REG_ICASE : REG_EXTENDED;  // учет регистра символов
  regcomp(&rx, template, flag_i);  // компиляция регулярного выражения
  FILE *f = fopen(file, "r");
  if (f != NULL) {
    int count_mem = file_memory(f) + 1;
    s21_grep(argument, count_mem, f, file, rx);
    regfree(&rx);
    fclose(f);
  } else
    fprintf(stderr, "grep: %s: No such file or directory\n", file);
}

void s21_grep(struct arguments *argument, int count_mem, FILE *f, char *file,
              regex_t rx) {
  char *c = (char *)malloc(count_mem);
  int flag_v = (argument->arg_v) ? 1 : 0;
  int count_mem_str = 0;  // счётчик валидных строк
  int str = 0;            // счётчик строк
  int print_f = false;  // печаталось ли название файла
  while (fgets(c, count_mem, f)) {
    str++;
    if (regexec(&rx, c, 0, NULL, 0) == flag_v) {
      if (argument->arg_file > 1 && !print_f && !argument->arg_l) {
        printf("%s:", file);
        print_f = true;
      }
      if (argument->arg_n == 1 && !argument->arg_l && !argument->arg_c) {
        printf("%d:", str);
      }
      if ((argument->arg_c || argument->arg_l) == 1) {
        count_mem_str++;
        continue;
      } else if ((strstr(c, "\n") == NULL))
        printf("%s\n", c);
      else
        printf("%s", c);
      print_f = false;
    }
  }

  if (argument->arg_c == 1 && argument->arg_file > 1 &&
      (count_mem_str == 0 || (argument->arg_l == 1 && count_mem_str > 0))) {
    printf("%s:", file);
  }
  if (argument->arg_c == 1 &&
      (argument->arg_l == 0 || (argument->arg_l == 1 && count_mem_str == 0)))
    printf("%d\n", count_mem_str);

  if (argument->arg_c == 1 && argument->arg_l == 1 && count_mem_str > 0) {
    printf("%d\n", 1);
  }
  if (argument->arg_l == 1 && count_mem_str > 0) printf("%s\n", file);
  free(c);
}
void create_template(char **template, char *temp) {  // создаем шаблон
  argument.counter_e++;
  *template = (char *)calloc(strlen(temp) + 1, 1);
  strcpy(*template, temp);
}

void add_template(char **template,
                  char *temp) {  // функция добавляет дополнительный шаблон к
                                 // существующему шаблону
  *template = realloc(*template, strlen(*template) + (strlen(temp) + 2));
  strcat(strcat(*template, "|"), temp);
}

void config_E(char *temp, char **template) {  // обработка аргумента опции -e
  if (argument.counter_e == 0) {
    create_template(template, temp);
  } else {
    add_template(template, temp);
  }
}

int file_memory(FILE *f) {  // определяем максимальный размер строки
  int mem = 0;
  while (fgetc(f) != EOF) mem++;
  rewind(f);
  return mem;
}