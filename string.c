#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: size_t length of string
 */
size_t _strlen(const char *s)
{
    size_t len = 0;

    if (!s)
        return 0;

    while (*s++)
        len++;

    return len;
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: int negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    return (*s1 - *s2);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: char* address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: char* pointer to the destination buffer
 */
char *_strcat(char *dest, const char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = '\0';

    return ret;
}

