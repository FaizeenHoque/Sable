#include "sable.h"

char **split_line(char *line) {
    int buffsize = 1024, position = 0;
    char **tokens = malloc(buffsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "%ssable: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position++] = token;
        if (position >= buffsize) {
            buffsize += 1024;
            tokens = realloc(tokens, buffsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "%ssable: Allocation error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *read_line() {
    int buffsize = 1024, position = 0;
    char *buffer = malloc(buffsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "%ssable: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position++] = c;
        }

        if (position >= buffsize) {
            buffsize += 1024;
            buffer = realloc(buffer, buffsize);
            if (!buffer) {
                fprintf(stderr, "%ssable: Allocation error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
    }
}
