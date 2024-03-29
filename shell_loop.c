#include "shell.h"

int execute_command(info_t *info, char **av);

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
    ssize_t r;
    int builtin_ret;

    do
    {
        clear_info(info);

        if (interactive(info))
            _puts("$ ");

        _eputchar(BUF_FLUSH);

        r = get_input(info);

        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);

            if (builtin_ret == -1)
                execute_command(info, av);
        }

        if (interactive(info) && r != -1)
            _putchar('\n');

        free_info(info, 0);

    } while (r != -1 && builtin_ret != -2);

    write_history(info);
    free_info(info, 1);

    if (!interactive(info) && info->status)
        exit(info->status);

    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);

        exit(info->err_num);
    }

    return builtin_ret;
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;

    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }

    return built_in_ret;
}

/**
 * execute_command - executes a non-builtin command
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: void
 */
int execute_command(info_t *info, char **av)
{
    char *path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }

    return 0;
}

