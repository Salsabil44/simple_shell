#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    char *path = NULL;
    char *path_copy = _strdup(pathstr);

    if (!path_copy)
        return NULL;

    char *token = _strtok(path_copy, ":");
    while (token != NULL)
    {
        path = _strcatdup(token, "/");
        path = _strcatdup(path, cmd);

        if (is_cmd(info, path))
        {
            free(path_copy);
            return path;
        }

        free(path);
        token = _strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

