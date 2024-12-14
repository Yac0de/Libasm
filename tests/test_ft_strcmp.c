#include <stdio.h>
#include <string.h>

int ft_strcmp(const char *s1, const char *s2);

void test_ft_strcmp() {
    printf("=== Testing ft_strcmp ===\n");

    struct {
        const char *s1;
        const char *s2;
        const char *description;
    } tests[] = {
        {"Hello", "Hello", "Identical strings"},
        {"Hello", "World", "Completely different strings"},
        {"", "NonEmpty", "Empty vs Non-empty"},
        {"Hello", "Hello!", "Different lengths"},
        {"Hello", "Hell", "Prefix match but different lengths"},
    };

    for (int i = 0; i < 5; i++) {
        int expected = strcmp(tests[i].s1, tests[i].s2);
        int result = ft_strcmp(tests[i].s1, tests[i].s2);

        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("Comparing '%s' and '%s'\n", tests[i].s1, tests[i].s2);
        printf("Expected: %d | Got: %d\n\n", expected, result);
    }
}