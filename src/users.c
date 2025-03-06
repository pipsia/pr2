#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include "users.h"

void print_users() {
    struct passwd *pw;
    setpwent();
    while ((pw = getpwent()) != NULL) {
        printf("User: %s, Home: %s\n", pw->pw_name, pw->pw_dir);
    }
    endpwent();
}
