#ifndef SABLE_H
#define SABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

#define TOK_DELIM " \t\r\n"

#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define BLUE   "\033[0;34m"
#define RESET  "\033[0m"

// Function declarations
void loop();

char *read_line();
char **split_line(char *line);

int sable_execute(char **args);
int sable_cd(char **args);
int sable_exit(char **args);

#endif
