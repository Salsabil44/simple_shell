#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT; // Initialize info_t structure

    // Use shell library function to handle file descriptor based on arguments
    handle_file_descriptor(&info, ac, av);

    // Populate environment list
    populate_env_list(&info);

    // Read command history
    read_history(&info);

    // Start the shell
    hsh(&info, av);

    return EXIT_SUCCESS;
}

