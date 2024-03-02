#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (!ptr || !(*ptr))
        return 0;

    free(*ptr);
    *ptr = NULL;
    return 1;
}

