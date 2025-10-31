#include "sable.h"

void loop() {
    char *line;
    char **args;
    int status = 1;
    char cwd[PATH_MAX];
    char *username = getenv("USER");

    do {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s%s%s:%s%s%s$ ", BLUE, username ? username : "user", RESET, GREEN, cwd, RESET);
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
