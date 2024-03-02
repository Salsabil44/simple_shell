#include "shell.h"

ssize_t shell_input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len)
    {
        shell_free(*buf);
        *buf = NULL;
        shell_signal(SIGINT, shell_sigintHandler);

        r = shell_getline(buf, &len_p, stdin);

        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }

            info->linecount_flag = 1;
            shell_remove_comments(*buf);
            shell_build_history_list(info, *buf, info->histcount++);

            *len = r;
            info->cmd_buf = buf;
        }
    }

    return r;
}

ssize_t shell_get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    shell_putchar(BUF_FLUSH);

    r = shell_input_buf(info, &buf, &len);

    if (r == -1)
        return -1;

    if (len)
    {
        j = i;
        p = buf + i;

        shell_check_chain(info, buf, &j, i, len);

        while (j < len)
        {
            if (shell_is_chain(info, buf, &j))
                break;

            j++;
        }

        i = j + 1;

        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return shell_strlen(p);
    }

    *buf_p = buf;
    return r;
}

ssize_t shell_read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;

    r = shell_read(info->readfd, buf, READ_BUF_SIZE);

    if (r >= 0)
        *i = r;

    return r;
}

int shell_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length)
        s = *length;

    if (i == len)
        i = len = 0;

    r = shell_read_buf(info, buf, &len);

    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = shell_strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = shell_realloc(p, s, s ? s + k : k + 1);

    if (!new_p)
        return p ? (shell_free(p), -1) : -1;

    if (s)
        shell_strncat(new_p, buf + i, k - i);
    else
        shell_strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;

    *ptr = p;
    return s;
}

void shell_sigintHandler(__attribute__((unused))int sig_num)
{
    shell_puts("\n");
    shell_puts("$ ");
    shell_putchar(BUF_FLUSH);
}

