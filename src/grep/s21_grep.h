#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "s21_grep.h"

#define false 0
#define true 1
int output(char flag, char argv[], char *optarg);
int l_function(int argc, char *argv[], char *optarg);
int h_function(int argc, char *argv[], char *optarg);
int output_no_flag(char argv[], char *optarg);
int f_function(int argc, char *argv[], char *optarg);

#endif  //  SRC_S21_GREP_H_