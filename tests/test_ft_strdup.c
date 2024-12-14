#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_strdup(const char *s);

void test_ft_strdup() {
    printf("=== Testing ft_strdup ===\n");

    const char *tests[] = {
        "Hello, world!",
        "",
        "A",
        "This is a longer string for testing ft_strdup.",
        "Special chars: \n\t\0Hidden Text",
    };

    for (int i = 0; i < 5; i++) {
        char *dup = ft_strdup(tests[i]);
        printf("Test %d: \"%s\"\n", i + 1, tests[i]);

        if (dup) {
            printf("Expected: \"%s\" | Got: \"%s\"\n", tests[i], dup);
            free(dup);
        } else {
            printf("Memory allocation failed!\n");
        }
        printf("\n");
    }
}