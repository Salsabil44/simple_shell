#include <shell.h>

/* Print history */
void _myhistory(void)
{
    struct hist_entry *he;
    int i = history_length;

    for (i = 0; i < history_length; i++)
    {
        he = current_history()->entries[i];
        printf("%4d %s\n", i + 1, he->line);
    }
}

/* Unset alias */
void unset_alias(const char *name)
{
    struct alias *ap;

    if ((ap = lookup_alias(name, -1)) == NULL)
    {
        printf("%s: %s not found\n", current_builtin->name, name);
        return;
    }

    unalias(name);
}

/* Set alias */
void set_alias(const char *name, const char *value)
{
    struct alias *ap;

    if (value == NULL)
    {
        unset_alias(name);
        return;
    }

    ap = add_alias(name, value);
    if (ap == NULL)
    {
        printf("%s: %s: %s\n", current_builtin->name, name, strerror(errno));
        return;
    }
}

/* Mimic the alias builtin (man alias) */
void _myalias(int argc, char **argv)
{
    if (argc == 1)
    {
        print_alias_table();
        return;
    }

    for (int i = 1; i < argc; i++)
    {
        char *p = strchr(argv[i], '=');
        if (p)
        {
            *p = '\0';
            set_alias(argv[i], p + 1);
        }
        else
        {
            print_alias(argv[i]);
        }
    }
}
