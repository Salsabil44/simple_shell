#include "shell.h"

/**
 * @brief Prints the current environment.
 * @param info Shell information.
 * @return Always 0.
 */
int shell_print_environment(ShellInfo *info)
{
    shell_print_list_str(info->environment);
    return 0;
}

/**
 * @brief Gets the value of an environment variable.
 * @param info Shell information.
 * @param name Environment variable name.
 * @return The value of the environment variable, or NULL if not found.
 */
char *shell_get_environment_variable(ShellInfo *info, const char *name)
{
    ShellList *node = info->environment;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * @brief Initializes a new environment variable or modifies an existing one.
 * @param info Shell information.
 * @return 0 on success, 1 on failure.
 */
int shell_set_environment_variable(ShellInfo *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (shell_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

/**
 * @brief Removes an environment variable.
 * @param info Shell information.
 * @return Always 0.
 */
int shell_unset_environment_variable(ShellInfo *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
        shell_unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * @brief Populates the environment linked list.
 * @param info Shell information.
 * @return Always 0.
 */
int shell_populate_environment_list(ShellInfo *info)
{
    ShellList *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        shell_add_node_end(&node, environ[i], 0);

    info->environment = node;
    return 0;
}

