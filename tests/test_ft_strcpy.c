#include <stdio.h>
#include <string.h>

char *ft_strcpy(char *dest, const char *src);

void test_ft_strcpy() {
    printf("=== Testing ft_strcpy ===\n");

    char dest[100];

    struct {
        const char *src;
        const char *description;
    } tests[] = {
        {"Hello, world!", "Basic string copy"},
        {"", "Copy empty string"},
        {"A", "Single character string"},
        {"This is a longer string with more text.", "Long string"},
        {"Hello\nWorld!", "String with special characters"},
    };

    for (int i = 0; i < 5; i++) {
        ft_strcpy(dest, tests[i].src);
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("Expected: %s | Got: %s\n\n", tests[i].src, dest);
    }
}