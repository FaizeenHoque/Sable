#include "sable.h"

int sable_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "sable: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0)
            perror("sable");
    }
    return 1;
}

int sable_exit(char **args) {
    return 0;
}
