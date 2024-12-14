#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);

void test_ft_strlen() {
    printf("=== Testing ft_strlen ===\n");

    // Test 1: Basic string
    printf("Test 1: \"Hello\"\n");
    printf("Expected: %lu | Got: %lu\n", strlen("Hello"), ft_strlen("Hello"));

    // Test 2: Empty string
    printf("Test 2: Empty string\n");
    printf("Expected: %lu | Got: %lu\n", strlen(""), ft_strlen(""));

    // Test 3: One-character string
    printf("Test 3: \"A\"\n");
    printf("Expected: %lu | Got: %lu\n", strlen("A"), ft_strlen("A"));

    // Test 4: Long string
    const char *long_str = "This is a long test string for ft_strlen!";
    printf("Test 4: Long string\n");
    printf("Expected: %lu | Got: %lu\n", strlen(long_str), ft_strlen(long_str));

    // Test 5: String with special characters
    printf("Test 5: Special chars \"Hello\\nWorld!\\t\\0Test\"\n");
    printf("Expected: %lu | Got: %lu\n", strlen("Hello\nWorld!\t\0Test"), ft_strlen("Hello\nWorld!\t\0Test"));
}