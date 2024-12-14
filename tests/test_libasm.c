#include <stdio.h>
#include <string.h>

// Test function declarations
void test_ft_strlen();
void test_ft_strcpy();
void test_ft_strcmp();
void test_ft_write();
void test_ft_read();
void test_ft_strdup();

typedef void (*test_func_t)(void);

int main(int argc, char *argv[]) {
    struct {
        const char *name;
        test_func_t func;
    } tests[] = {
        {"ft_strlen", test_ft_strlen},
        {"ft_strcpy", test_ft_strcpy},
        {"ft_strcmp", test_ft_strcmp},
        {"ft_write", test_ft_write},
        {"ft_read", test_ft_read},
        {"ft_strdup", test_ft_strdup},
    };

    if (argc == 1) {
        for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
            tests[i].func();
            printf("\n");
        }
    } else {
        for (int i = 1; i < argc; i++) {
            int found = 0;
            for (size_t j = 0; j < sizeof(tests) / sizeof(tests[0]); j++) {
                if (strcmp(argv[i], tests[j].name) == 0) {
                    tests[j].func();
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("❌ Test \"%s\" not found!\n", argv[i]);
            }
        }
    }

    return 0;
}
