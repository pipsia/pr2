#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>  // Для memset
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

    // Флаги для отслеживания выполнения команд
    bool users_printed = false;
    bool processes_printed = false;
    bool help_printed = false;

    // Буфер для хранения вывода
    char output_buffer[4096];  // Буфер на 4 КБ
    memset(output_buffer, 0, sizeof(output_buffer));  // Очищаем буфер

    // Временный файл для хранения вывода
    FILE *temp_output = tmpfile();
    if (temp_output == NULL) {
        perror("tmpfile");
        return EXIT_FAILURE;
    }

    // Сохраняем оригинальный stdout
    FILE *original_stdout = stdout;

    while ((opt = getopt(argc, argv, "upe:l:h")) != -1) {
        switch (opt) {
            case 'u':
                if (!users_printed) {
                    // Перенаправляем stdout во временный файл
                    stdout = temp_output;
                    print_users();
                    stdout = original_stdout;  // Восстанавливаем stdout
                    users_printed = true;
                }
                break;
            case 'p':
                if (!processes_printed) {
                    stdout = temp_output;
                    print_processes();
                    stdout = original_stdout;
                    processes_printed = true;
                }
                break;
            case 'l':
                log_path = optarg;
                break;
            case 'e':
                errors_path = optarg;
                break;
            case 'h':
                if (!help_printed) {
                    print_help();
                    help_printed = true;
                }
                return 0;
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                print_help();
                return 1;
        }
    }

    // Если указан аргумент -l, записываем вывод в файл
    if (log_path != NULL) {
        FILE *log_file = freopen(log_path, "w", stdout);
        if (log_file == NULL) {
            perror("freopen");
            return EXIT_FAILURE;
        }

        // Читаем данные из временного файла и записываем в log_file
        rewind(temp_output);  // Перемещаем указатель в начало временного файла
        char ch;
        while ((ch = fgetc(temp_output)) != EOF) {
            fputc(ch, log_file);
        }

        fclose(log_file);
    } else {
        // Если аргумент -l не указан, выводим данные на экран
        rewind(temp_output);
        char ch;
        while ((ch = fgetc(temp_output)) != EOF) {
            fputc(ch, stdout);
        }
    }

    // Закрываем временный файл
    fclose(temp_output);

    // Перенаправление ошибок (если указан аргумент -e)
    if (errors_path != NULL) {
        redirect_errors_to_file(errors_path);
    }

    return 0;
}
