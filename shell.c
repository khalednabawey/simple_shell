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
