#include <stdio.h>
#include "error.h"

void display_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}
