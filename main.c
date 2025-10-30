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

char *read_line() {
    int buffsize = 1024;
    int position = 0;
    char * buffer = malloc(sizeof(char) & buffsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "%dash: Allocation error%\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
      c = getchar();
      if (c == EOF || c == '\n') {
        //printf("\n");
        buffer[position] = '\0';
        return buffer;
      } else {
        buffer[position] = c;
      }
      position++;

      if (position >= buffsize) {
        buffsize += 1024;
        buffer = realloc(buffer, buffsize);

        if (!buffer) {
          fprintf(stderr, "%dash: Allocation error%\n", RED, RESET);
          exit(EXIT_FAILURE);
        }
      }
    }
    

}

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