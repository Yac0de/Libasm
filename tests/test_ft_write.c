#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

void test_ft_write() {
    printf("=== Testing ft_write ===\n");

    // Test 1: Standard output
    printf("Test 1: Writing to stdout\n");
    ft_write(1, "Hello, stdout!\n", 15);

    // Test 2: Invalid file descriptor
    printf("\nTest 2: Invalid file descriptor\n");
    ssize_t ret = ft_write(-1, "This will fail\n", 16);
    printf("Expected: -1 | Got: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));

    // Test 3: Writing to a file
    printf("\nTest 3: Writing to a file\n");
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }
    ret = ft_write(fd, "File content written.\n", 23);
    printf("Bytes Written: %zd\n", ret);
    close(fd);

    // Test 4: Writing empty string
    printf("\nTest 4: Writing empty string\n");
    ret = ft_write(1, "", 0);
    printf("Expected: 0 | Got: %zd\n", ret);
}