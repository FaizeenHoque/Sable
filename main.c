#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>   // for getcwd()
#include <limits.h>   // for PATH_MAX


#define TOK_DELIM " \t\r\n"
#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define BLUE   "\033[0;34m"
#define RESET  "\033[0m"

char *read_line();
char **split_line(char *);
int sable_exit(char **);
int sable_execute(char **);
int sable_cd(char **);

int sable_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "sable: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("sable");
        }
    }
    return 1;
}

int sable_execute(char **args) {
  if (args[0] == NULL)
      return 1;

  if (strcmp(args[0], "exit") == 0)
      return sable_exit(args);

  if (strcmp(args[0], "cd") == 0)
      return sable_cd(args);

  pid_t cpid;
  int status;
  cpid = fork();

  if (cpid == 0) {
    if (execvp(args[0], args) < 0)
      printf("%ssable: Command not found: %s%s\n", RED, args[0], RESET);
    exit(EXIT_FAILURE);
  } else if (cpid < 0) {
    printf("%ssable: Error forking%s\n", RED, RESET);
  } else {
    waitpid(cpid, &status, WUNTRACED);
  }

  return 1;
}

int sable_exit(char **args)
{
    return 0;
}

char **split_line(char *line) {
  int buffsize = 1024, position = 0;
  char **tokens = malloc(buffsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "%s sable: Allocation error %s\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position ++;

    if (position >= buffsize) {
      buffsize += 1024;
      tokens = realloc(tokens, buffsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "%s sable: Allocation error %s\n", RED, RESET);
        exit(EXIT_FAILURE);
      }
    }
    
    token = strtok(NULL, TOK_DELIM);
  }
  
  tokens[position] = NULL;
  return tokens;
}

char *read_line() {
    int buffsize = 1024;
    int position = 0;
    char *buffer = malloc(buffsize);

    int c;

    if (!buffer) {
        fprintf(stderr, "%s sable: Allocation error %s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
      c = getchar();
      if (c == EOF || c == '\n') {
        buffer[position] = '\0';
        return buffer;
      } else {
        buffer[position] = c;
      }
      position++;

      if (position >= buffsize) {
        buffsize += 1024;
        char *new_buffer = realloc(buffer, buffsize);

        if (!buffer) {
          fprintf(stderr, "%s sable: Allocation error %s\n", RED, RESET);
          exit(EXIT_FAILURE);
        }
      }
    }
}

void loop() {
    char *line;
    char **args;
    int status = 1;
    char cwd[PATH_MAX];      
    char *username = getenv("USER");  

    do {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s%s%s:%s%s%s$ ", 
                   BLUE, username ? username : "user", RESET,
                   GREEN, cwd, RESET);
        } else {
            printf("%s%s%s:?$ ", BLUE, username ? username : "user", RESET);
        }
        fflush(stdout);

        line = read_line();
        args = split_line(line);
        status = sable_execute(args);
        free(line);
        free(args);
    } while (status);
}

int main() {
    loop();
    return 0;
}
