#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

ssize_t ft_read(int fd, void *buf, size_t count);

void test_ft_read() {
    printf("=== Testing ft_read ===\n");

    char buf[100];

    // Test 1: Reading from a pipe (simulates stdin)
    printf("Test 1: Reading from a pipe\n");
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }
    write(pipefd[1], "Pipe test content", 18);
    close(pipefd[1]);

    ssize_t ret = ft_read(pipefd[0], buf, sizeof(buf) - 1);
    if (ret >= 0) {
        buf[ret] = '\0';
        printf("Pipe content: %s\n", buf);
    } else {
        perror("ft_read (pipe)");
    }
    close(pipefd[0]);

    // Test 2: Reading from a file
    printf("\nTest 2: Reading from a file\n");
    int fd_write = open("test_input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_write < 0) {
        perror("Error creating test file");
        return;
    }
    write(fd_write, "Test file content\n", 18);
    close(fd_write);

    int fd = open("test_input.txt", O_RDONLY);
    if (fd < 0) {
        perror("open (test_input.txt)");
        return;
    }
    ret = ft_read(fd, buf, sizeof(buf) - 1);
    if (ret >= 0) {
        buf[ret] = '\0';
        printf("File content: %s\n", buf);
    } else {
        perror("ft_read (file)");
    }
    close(fd);

    // Test 3: Invalid file descriptor
    printf("\nTest 3: Invalid file descriptor\n");
    ret = ft_read(-1, buf, sizeof(buf));
    printf("Expected: -1 | Got: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));
}