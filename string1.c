#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;

    char *result = dest;

    while ((*dest++ = *src++))
        ;

    return result;
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    if (!str)
        return NULL;

    size_t length = _strlen(str);
    char *duplicate = malloc(length + 1);

    if (!duplicate)
        return NULL;

    _strcpy(duplicate, str);
    return duplicate;
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(const char *str)
{
    if (!str)
        return;

    write(1, str, _strlen(str));
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

