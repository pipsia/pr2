#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "log.h"
#include "errors.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int opt;
    char *log_path = NULL;
    char *errors_path = NULL;

    while ((opt = getopt(argc, argv, "upe:l:h")) != -1) {
        switch (opt) {
            case 'u':
                print_users();
                break;
            case 'p':
                print_processes();
                break;
            case 'l':
                log_path = optarg;
                redirect_output_to_file(log_path);
                break;
            case 'e':
                errors_path = optarg;
                redirect_errors_to_file(errors_path);
                break;
            case 'h':
                print_help();
                return 0;
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                print_help();
                return 1;
        }
    }

    return 0;
}
