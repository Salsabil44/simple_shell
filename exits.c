#include "shell.h"

/**
 * @brief Copies a string up to a specified number of characters.
 * @param dest The destination string to be copied to.
 * @param src The source string.
 * @param n The maximum number of characters to copy.
 * @return A pointer to the destination string.
 */
char *shell_strncpy(char *dest, const char *src, int n)
{
    char *s = dest;

    while (*src != '\0' && n > 0)
    {
        *dest++ = *src++;
        n--;
    }

    while (n > 0)
    {
        *dest++ = '\0';
        n--;
    }

    return s;
}

/**
 * @brief Concatenates two strings, up to a specified number of characters.
 * @param dest The first string.
 * @param src The second string.
 * @param n The maximum number of bytes to be used.
 * @return A pointer to the concatenated string.
 */
char *shell_strncat(char *dest, const char *src, int n)
{
    char *s = dest;

    while (*dest != '\0')
        dest++;

    while (*src != '\0' && n > 0)
    {
        *dest++ = *src++;
        n--;
    }

    if (n > 0)
        *dest = '\0';

    return s;
}

/**
 * @brief Locates a character in a string.
 * @param s The string to be parsed.
 * @param c The character to look for.
 * @return A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *shell_strchr(const char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
            return (char *)s;
        s++;
    }

    return NULL;
}

