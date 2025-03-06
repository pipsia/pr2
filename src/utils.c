#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Добавьте этот заголовочный файл
#include "utils.h"

void check_file_access(const char *path) {
    if (access(path, W_OK) == -1) {
        perror("access");
        exit(EXIT_FAILURE);
    }
}
