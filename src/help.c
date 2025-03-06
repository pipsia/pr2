#include <stdio.h>
#include "help.h"

void print_help() {
    printf("Usage: practical_work_2 [options]\n");
    printf("Options:\n");
    printf("  -u, --users       Print list of users and their home directories\n");
    printf("  -p, --processes   Print list of running processes\n");
    printf("  -l PATH           Redirect output to the specified file\n");
    printf("  -e PATH           Redirect errors to the specified file\n");
    printf("  -h, --help        Print this help message\n");
}
