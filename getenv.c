#include "shell.h"

/**
 * @brief Returns the string array copy of our environ.
 * @param info Structure containing potential arguments.
 * @return The string array copy of our environ.
 */
char **shell_get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = shell_list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * @brief Remove an environment variable.
 * @param info Structure containing potential arguments.
 * @param var The string env var property.
 * @return 1 on delete, 0 otherwise.
 */
int shell_unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = shell_starts_with(node->str, var);

        if (p && *p == '=')
        {
            info->env_changed = shell_delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }

        node = node->next;
        i++;
    }

    return info->env_changed;
}

/**
 * @brief Initialize a new environment variable, or modify an existing one.
 * @param info Structure containing potential arguments.
 * @param var The string env var property.
 * @param value The string env var value.
 * @return Always 0.
 */
int shell_setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = shell_malloc(shell_strlen(var) + shell_strlen(value) + 2);

    if (!buf)
        return 1;

    shell_strcpy(buf, var);
    shell_strcat(buf, "=");
    shell_strcat(buf, value);

    node = info->env;

    while (node)
    {
        p = shell_starts_with(node->str, var);

        if (p && *p == '=')
        {
            shell_free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }

        node = node->next;
    }

    shell_add_node_end(&(info->env), buf, 0);
    shell_free(buf);
    info->env_changed = 1;

    return 0;
}

