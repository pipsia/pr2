#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

void redirect_errors_to_file(const char *path) {
    FILE *file = freopen(path, "w", stderr);
    if (file == NULL) {
        perror("freopen");
        exit(EXIT_FAILURE);
    }
}
