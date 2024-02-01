#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arguments {
  int arg_e, arg_i, arg_v, arg_c, arg_l, arg_n, counter_e, arg_file;
} argument;

void set_settings(struct arguments *argument) {
  argument->arg_e = 0;
  argument->arg_i = 0;
  argument->arg_v = 0;
  argument->arg_c = 0;
  argument->arg_l = 0;
  argument->arg_n = 0;
  argument->arg_file = 0;
  argument->counter_e = 0;
}

void set_options(int argc, char *argv[], struct arguments *argument,
                 char **template);
void open_file(char *file, struct arguments *argument, char *template);
void s21_grep(struct arguments *argument, int count_mem, FILE *f, char *file,
              regex_t rx);
void create_template(char **template, char *temp);
void add_template(char **template, char *temp);
void config_E(char *temp, char **template);
int file_memory(FILE *f);