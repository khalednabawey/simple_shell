#include "main.h"

/**
 * parse_input - Parses user input into individual commands and arguments
 * @input: User input to be parsed
 * @args: Array of arguments
 *
 * Return: Number of commands and arguments
 */
int parse_input(char *input, char **args)
{
	int index = 0;

	args[index] = strtok(input, " ");
	while (index < 10 && args[index] != NULL)
	{
		index++;
		args[index] = strtok(NULL, " ");
	}
	return (index);
}
/**
 * search_command - Searches and executes the specified command
 * @args: Array of arguments
 *
 * Return: None
 */

void search_command(char **args)
{
	char *command, *path, *path_copy, *directory, *full_command;

	command = strdup(args[0]);
	if (command == NULL)
		exit(1);

}
