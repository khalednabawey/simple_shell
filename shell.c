#include "main.h"

#define MAX_INPUT_SIZE 1024

/**
 * parse_input - Parse user input into arguments.
 * @input: User input to be parsed.
 *
 * Return: Array of arguments (char **).
 */
char **parse_input(char *input)
{
	char **args = malloc(MAX_INPUT_SIZE * sizeof(char *));
	char *token;
	int index;

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " ");

	index = 0;

	while (token != NULL)
	{
		args[index] = token;
		token = strtok(NULL, " ");
		index++;
	}

	args[index] = NULL;
	return (args);
}

/**
 * get_path - Get the full path of a command.
 * @command: Command to find the full path for.
 *
 * Return: Full path of the command (char *).
 */
char *get_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *directory = strtok(path_copy, ":");

	while (directory != NULL)
	{
		char *full_command = malloc(strlen(directory) + strlen(command) + 2);

		if (full_command == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_command, "%s/%s", directory, command);
		if (access(full_command, X_OK) == 0)
		{
			free(path_copy);
			return (full_command);
		}
		free(full_command);
		directory = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Execute a command with arguments.
 * @args: Array of arguments to execute.
 *
 * Return: Status of the execution (int).
 */
int execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
	return (0);
}

/**
 * main - Main function of the simple shell.
 *
 * Return: Exit status (int).
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	char **args;
	char *path;

	while (1)
	{
		printf("($) ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
			break;

		args = parse_input(input);

		if (args[0] == NULL)
			continue;
		if (strcmp(args[0], "env") == 0)
			continue;
		path = get_path(args[0]);

		if (path == NULL)
		{
			printf("%s: command not found\n", args[0]);
			continue;
		}
		execute_command(args);
		free(args);
	}
	return (0);
}
