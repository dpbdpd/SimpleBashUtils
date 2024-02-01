#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_with_line_numbers(FILE* file, bool flag_b, bool flag_n);
void print_with_blank_lines(FILE* file);
void print_with_tabs(FILE* file);
void print_with_tabs_T(FILE* file);
void print_with_ends(FILE* file);
void print_with_ends_E(FILE* file);
void print_with_nonprinting_chars(FILE* file);

#endif