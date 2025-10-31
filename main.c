#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <sys/types.h>
#include <unistd.h>
// #include <sys/wait.h>

#include <windows.h>

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"

char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);

// int dash_execute(char **args) {
//   pid_t cpid;
//   int status;

//   if (strcmp(args[0], "exit") == 0) {
//     return dash_exit(args);
//   }

//   cpid = fork();

//   if (cpid == 0) {
//     if (execvp(args[0], args) < 0)
//       printf("%sdash: Command not found: %s%s\n", RED, args[0], RESET);
//     exit(EXIT_FAILURE);
//   } else if (cpid < 0) {
//     printf("%sdash: Error forking%s\n", RED, RESET);
//   } else {
//     waitpid(cpid, &status, WUNTRACED);
//   }

//   return 1;
// }

int dash_execute(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        return dash_exit(args);
    }

    // Build command line for CreateProcess
    char cmdline[1024] = "";
    for (int i = 0; args[i] != NULL; i++) {
        strcat(cmdline, args[i]);
        if (args[i + 1] != NULL)
            strcat(cmdline, " ");
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the process
    if (!CreateProcess(
            NULL,          // Application name
            cmdline,       // Command line
            NULL,          // Process handle not inheritable
            NULL,          // Thread handle not inheritable
            FALSE,         // Set handle inheritance to FALSE
            0,             // No creation flags
            NULL,          // Use parent's environment block
            NULL,          // Use parent's starting directory 
            &si,           // Pointer to STARTUPINFO structure
            &pi)           // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("%sdash: Command not found: %s%s\n", RED, args[0], RESET);
        return 1;
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 1;
}

int dash_exit(char **args)
{
	return 0;
}

char **split_line(char *line) {
  int buffsize = 1024, position = 0;
  char **tokens = malloc(buffsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "%dash: Allocation error%\n", RED, RESET);
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
        fprintf(stderr, "%dash: Allocation error%\n", RED, RESET);
        exit(EXIT_FAILURE);
      }

      token = strtok(NULL, TOK_DELIM);
    }

    tokens[position] = NULL;

    return tokens;
  }
}

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