#include "shell.h"

/**
 * @brief Writes a string to the specified file descriptor.
 * @param str The string to be printed.
 * @param fd The file descriptor to write to.
 * @return The number of characters written.
 */
int shell_puts_fd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        count += shell_write_fd(*str++, fd);
    }

    return count;
}

/**
 * @brief Writes a character to the specified file descriptor.
 * @param c The character to print.
 * @param fd The file descriptor to write to.
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int shell_write_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        shell_write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * @brief Writes a string to stderr.
 * @param str The string to be printed.
 * @return The number of characters written.
 */
int shell_eputs(char *str)
{
    return shell_puts_fd(str, 2); // 2 corresponds to stderr
}

/**
 * @brief Writes a character to stderr.
 * @param c The character to print.
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int shell_eputchar(char c)
{
    return shell_write_fd(c, 2); // 2 corresponds to stderr
}

/**
 * @brief Writes a character to the specified file descriptor.
 * @param c The character to print.
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int shell_putfd(char c, int fd)
{
    return shell_write_fd(c, fd);
}

