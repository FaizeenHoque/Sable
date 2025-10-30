#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"

char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);



void loop() {
  char *line;
  char **args;
  int status = 1;

  do {
    printf("> ");
    line = read_line();
    args = split_line(line);
    status = dash_execute(args);
    free(line);
    free(args);
  } while (status);
}


int main() {
    loop();
    return 0;
}