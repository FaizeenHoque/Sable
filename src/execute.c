#include "sable.h"

int sable_execute(char **args) {
    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "exit") == 0)
        return sable_exit(args);

    if (strcmp(args[0], "cd") == 0)
        return sable_cd(args);

    pid_t cpid = fork();
    int status;

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
