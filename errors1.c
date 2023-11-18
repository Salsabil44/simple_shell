#include "shell.h"

#define MAX_DIGITS 50

/**
 * @brief Converts a string to an integer.
 * @param s The string to be converted.
 * @return 0 if no numbers in the string, converted number otherwise.
 *         -1 on error.
 */
int shell_erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * @brief Prints an error message.
 * @param info The parameter & return info struct.
 * @param estr String containing specified error type.
 */
void shell_print_error(info_t *info, char *estr)
{
    shell_eputs(info->fname);
    shell_eputs(": ");
    shell_print_d(info->line_count, STDERR_FILENO);
    shell_eputs(": ");
    shell_eputs(info->argv[0]);
    shell_eputs(": ");
    shell_eputs(estr);
    shell_eputchar('\n');
}

/**
 * @brief Prints a decimal (integer) number (base 10).
 * @param input The input number.
 * @param fd The file descriptor to write to.
 * @return Number of characters printed.
 */
int shell_print_d(int input, int fd)
{
    int count = 0;

    if (input < 0)
    {
        shell_eputchar('-');
        count++;
        input = -input;
    }

    count += shell_put_unsigned_d((unsigned int)input, fd);

    return count;
}

/**
 * @brief Converts a number to a string.
 * @param num The number.
 * @param base The base.
 * @param flags Argument flags.
 * @return The string representation of the number.
 */
char *shell_convert_number(long int num, int base, int flags)
{
    static char buffer[MAX_DIGITS];
    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    char sign = 0;
    char *ptr = &buffer[MAX_DIGITS - 1];

    *ptr = '\0';

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        num = -num;
        sign = '-';
    }

    do
    {
        *--ptr = array[num % base];
        num /= base;
    } while (num != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * @brief Removes comments from a string.
 * @param buf Address of the string to modify.
 */
void shell_remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}

