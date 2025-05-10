#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getValidatedIntegerInput(const char *prompt) {
    char input[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &value) == 1)
                return value;
            else
                printf(" Invalid input. Please enter a valid number.\n");
        }
    }
}
