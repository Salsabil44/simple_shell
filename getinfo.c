#include "shell.h"

/**
 * @brief Initializes info_t struct.
 * @param info Struct address.
 */
void shell_clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * @brief Initializes info_t struct.
 * @param info Struct address.
 * @param av Argument vector.
 */
void shell_set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = shell_strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = shell_malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = shell_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        shell_replace_alias(info);
        shell_replace_vars(info);
    }
}

/**
 * @brief Frees info_t struct fields.
 * @param info Struct address.
 * @param all True if freeing all fields.
 */
void shell_free_info(info_t *info, int all)
{
    shell_ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            shell_free(info->arg);
        if (info->env)
            shell_free_list(&(info->env));
        if (info->history)
            shell_free_list(&(info->history));
        if (info->alias)
            shell_free_list(&(info->alias));
        shell_ffree(info->environ);
        info->environ = NULL;
        shell_bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        shell_putchar(BUF_FLUSH);
    }
}

